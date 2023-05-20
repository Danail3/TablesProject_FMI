#include "Table.h"
#include <fstream>
#include <sstream>
//#include <string.h>

static int prec(char c)
{
	if (c == '^')
		return 3;
	else if (c == '/' || c == '*')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}

static int checkLengthOfDouble(double num)
{
	unsigned digitsBeforeDot = 0;
	while (num >= 1)
	{
		num /= 10;
		digitsBeforeDot++;
	}
	return digitsBeforeDot;
}

void Table::fillArrayWithLenghtOfEachRow(Row& row, Vector<int>& arr) const
{
	for (size_t i = 1; i <= row.getValues().getSize(); i++)
	{
		int lengthValue = 0;
		if (row.getValues()[i - 1].getType() == Types::formula)
		{
			//Value newValue(row.getValues()[i - 1].getString());
			calculateFormula(row[i - 1]);
			//lengthValue = newValue.getString().length();//getLengthOfDouble
		}
		lengthValue = row.getValues()[i - 1].getString().length();
		if (row.getValues().getSize() > arr.getSize() && (i > arr.getSize() || arr.getSize() == 0))
		{
			arr.pushBack(std::move(lengthValue));
		}
		else if (lengthValue > arr[i - 1])
		{
			arr.popAt(i - 1);
			arr.pushAt(std::move(lengthValue), i - 1);
		}
	}
}

void Table::getMaxLengthFromEachColumn(Vector<int>& arr)
{
	for (size_t i = 0; i < rows.getSize(); i++)
	{
		fillArrayWithLenghtOfEachRow(rows[i], arr);
	}
}


Table::Table(Vector<Row>& newRows)
{
	size_t sizeOfVector = newRows.getSize();
	if (sizeOfVector == 0)
	{
		throw std::invalid_argument("There are not any values!");
	}
	for (size_t i = 0; i < sizeOfVector; i++)
	{
		rows.pushBack(std::move(newRows[i]));//pravilno li e da e move
		//setRow(newRows[i], i);
	}
}

void Table::exportDataFromFile(std::fstream& fs)
{
	size_t index = 0;
	while (!fs.eof())
	{
		Row currRow;
		currRow.readRow(fs);
		rows.pushBack(currRow);
	}
	return;
}

void Table::saveDataToFile(std::fstream& fs) const
{
	for (size_t i = 0; i < rows.getSize(); i++)
	{
		rows[i].saveRow(fs);
	}
}

void Table::editCell(size_t numberRow, size_t numberColumn, const MyString& str)
{
	int index = rows[numberRow].getValues().getSize();
	if (numberRow > rows.getSize() || numberColumn > index)
	{
		throw std::invalid_argument("Invalid index!");
	}
	rows[numberRow][numberColumn].setValue(str);
}

bool checkIfStringIsNumber(const MyString& str)
{
	for (size_t i = 1; i < str.length() - 1; i++)
	{
		if (str[i] != '.' && (str[i] < '0' || str[i] > '9'))
		{
			return false;
		}
	}
	return true;
}

void Table::getValueFromCell(MyString& str) const
{

	double resultCell = 0;
	int ind1 = str[1] - '0';
	int ind2 = str[3] - '0';
	str = rows[ind1 - 1][ind2 - 1].getString();
	if (!isNumber(str))
	{
		if (!checkIfStringIsNumber(str))
		{
			str = "0";
		}
		else
		{
			str = str.substr(1, str.length() - 2);
		}
	}
}
MyString Table::infixToPostfix(const MyString& s, Vector<double>& doubleArr, Vector<char>& operations) const //Idea Taken From geeksforgeeks
{
	Vector<char> st;
	MyString result;

	std::stringstream ss(s.c_str());
	ss.ignore(2);
	for (int i = 2; i <= s.length() - 1; i += 2)
	{
		MyString currNum;
		if (ss.eof())
		{
			break;
		}
		ss >> currNum;
		if (isCell(currNum))
		{
			getValueFromCell(currNum);
			if (s == currNum)
			{
				throw std::exception("The cell you selected is the same. Pls enter different value");//kato go catch-na da vrushta 0
			}
			else
			{
				while (Value(currNum).getType() == Types::formula)
				{
					throw std::exception("The cell you select should not contain another cell. Pls enter different value");//kato go catch-na da vrushta 0
				}
			}
		}
		if (currNum == '(')
		{
			st.pushBack('(');
		}
		else if (currNum == ')')
		{
			while (st[st.getSize() - 1] != '(')
			{
				result += st[st.getSize() - 1];
				result += ' ';

				st.popBack();
			}
			st.popBack();
		}
		else if (currNum == '*' || currNum == '+' || currNum == '-' || currNum == '^' || currNum == '/')
		{
			while (!st.empty() && prec(currNum[0]) <= prec(st[st.getSize() - 1]))
			{
				result += st[st.getSize() - 1];
				result += ' ';
				st.popBack();
			}
			st.pushBack(currNum[0]);
		}
		else
		{
			MyString copyOfCurrNums;
			if (currNum.length() == 0)
			{
				currNum += "0";
			}
			copyOfCurrNums += currNum;
			result += currNum;
			result += ' ';
			doubleArr.pushBack(std::stod(copyOfCurrNums.c_str()));
		}
	}
	while (!st.empty())
	{
		result += st[st.getSize() - 1];
		result += ' ';
		st.popBack();
	}

	for (size_t i = 0; i < result.length(); i++)
	{
		if (result[i] == '*' || result[i] == '+' || result[i] == '-' || result[i] == '^' || result[i] == '/')
		{
			operations.pushBack(result[i]);
		}
	}
	//std::cout << result << std::endl;
	return result;
}

double Table::getResult(char ch, double num1, double num2) const
{
	int pow = num2;
	int copyNum1 = num1;

	switch (ch)
	{
	case '+':
		return num1 + num2;
	case '-':
		return num1 - num2;
	case '^':
		--num2;
		while (num2 != 0)
		{
			if (num2 == 0)
			{
				return 1;
			}
			num1 *= copyNum1;
			num2--;
		}
		return num1;
	case '*':
		return num1 * num2;
	case '/':
		if (num2 == 0)
		{
			throw std::invalid_argument("Operation cannot be done!"); //da q catch-na kat printq
		}
		return num1 / num2;
	default:
		return -1;
	}
}

size_t Table::findIndOfOperation(const MyString& str, char op, size_t startIndex, size_t& indexUntilNow) const
{
	int counterSpaces = startIndex;
	for (size_t i = indexUntilNow; i <= str.length(); i++)
	{
		if (op == str[i])
		{
			indexUntilNow = i + 1;
			return counterSpaces;
		}
		else if (str[i] == ' ')
		{
			counterSpaces++;
		}
	}
	return counterSpaces;
}

void Table::changeTheValueOfFormula(double num, Value& value) const
{
	std::stringstream ss;
	ss << num;
	char buff[1024]{};
	ss.getline(buff, 1024);
	MyString strCurr(buff);
	value.setValue(strCurr);
}

void Table::calculateFormula(Value& value) const
{
	Vector<double> nums;
	Vector<char> operations;
	MyString str = infixToPostfix(value.getString(), nums, operations);
	int indOp = 0;
	int reduceIndOp = 0;
	size_t indexUntilNow = 0;
	while (nums.getSize() != 1)
	{
		indOp = findIndOfOperation(str, operations[0], indOp, indexUntilNow);
		double currRes = 0;
		try
		{
			currRes = getResult(operations[0], nums[indOp - reduceIndOp - 2], nums[indOp - reduceIndOp - 1]);
		}
		catch (const std::invalid_argument& exe)
		{
			std::cout << exe.what() << std::endl;
			value.setValue("\"ERROR\"");
			return;
		}
		
		nums.popAt(indOp - reduceIndOp - 2);
		nums.pushAt(currRes, indOp - reduceIndOp - 2);
		nums.popAt(indOp - reduceIndOp - 1);
		reduceIndOp += 2;
		operations.popAt(0);
	}
	changeTheValueOfFormula(nums[0], value);
}

void Table::addSpaces(int& conditionValue) const
{
	while (conditionValue != 0)
	{
		std::cout << " ";
		conditionValue--;
	}
}


unsigned Table::getMaxValueInRows() const
{
	unsigned maxValues = 0;
	for (size_t i = 0; i < rows.getSize(); i++)
	{
		if (rows[i].getValues().getSize() > maxValues)
		{
			maxValues = rows[i].getValues().getSize();
		}
	}
	return maxValues;
}

void Table::printRow(const Row& row, Vector<int>& numberOfSpaces) const {
	if (row.getValues().getSize() != 0)
	{
		std::cout << "| ";
	}
	for (size_t i = 0; i < row.getValues().getSize(); i++)
	{
		int copyNumberOfSpaces = numberOfSpaces[i];
		int spacesTaken = row.getValues()[i].getString().length();
		int spacesLeftToPrint = copyNumberOfSpaces - spacesTaken;
		addSpaces(spacesLeftToPrint);
		std::cout << row.getValues()[i].getString();

		if (i != row.getValues().getSize() - 1)
		{
			std::cout << " | ";
		}
	}
	if (row.getValues().getSize() != 0)
	{
		std::cout << " |";
		std::cout << std::endl;
	}
}

void Table::printTable() {
	unsigned maxValuesOnRow = getMaxValueInRows();
	Vector<int> numberOfSpaces(maxValuesOnRow);
	getMaxLengthFromEachColumn(numberOfSpaces);
	for (size_t i = 0; i < rows.getSize(); i++)
	{
		printRow(rows[i], numberOfSpaces);
	}
}