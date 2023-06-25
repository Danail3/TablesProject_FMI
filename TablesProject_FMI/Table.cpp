#include "Table.h"
#include <fstream>
#include <sstream>
#include <windows.h>
#include "GlobalConstants.h"
#include "Helper.h"

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

//gets the length of a double
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

//makes array with max width from each column in a row
void Table::fillArrayWithLenghtOfEachRow(Row& row, Vector<int>& arr) const
{
	size_t valuesCount = row.getValuesCount();
	for (size_t i = 1; i <= valuesCount; i++)
	{
		size_t lengthValue = 0;
		if (row[i - 1]->getType() == Types::formula)
		{
			calculateFormula(row[i - 1]);
		}
		lengthValue = row[i - 1]->getString().length();
		if (row.getValuesCount() > arr.getSize() && (i > arr.getSize() || arr.getSize() == 0))
		{
			arr.pushBack(std::move(lengthValue));
		}
		else if (lengthValue > arr[i - 1])
		{
			arr.popAt(i - 1);
			arr.pushAt(lengthValue, i - 1);
		}
	}
}

void Table::getMaxLengthFromEachColumn(Vector<int>& arr)
{
	size_t rowsCount = rows.getSize();
	for (size_t i = 0; i < rowsCount; i++)
	{
		fillArrayWithLenghtOfEachRow(rows[i], arr);
	}
}

void Table::exportDataFromFile(std::fstream& fs)
{
	size_t index = 0;
	size_t rowIndex = 0;
	while (!fs.eof())
	{
		Row currRow;
		rowIndex++;
		try
		{
			currRow.readRow(fs, rowIndex);
			rows.pushBack(currRow);

		}
		catch (const std::exception& exe)
		{
			std::cout << "On line " << rowIndex << exe.what() << std::endl;
			std::cout << "Line " << rowIndex << " will not be printed!" << std::endl;
		}

	}
	std::cout << "Table loaded!" << std::endl;
	system("pause");
	system("cls");
}

void Table::saveDataToFile(std::fstream& fs) const
{
	size_t rowsCount = rows.getSize();
	for (size_t i = 0; i < rowsCount; i++)
	{
		rows[i].saveRow(fs);
		if (i != rows.getSize() - 1)
		{
			fs << std::endl;
		}
	}
}

void Table::editCell(size_t numberRow, size_t numberColumn, const MyString& str)
{
	int index = rows[numberRow - 1].getValuesCount();
	if (numberRow - 1 >= rows.getSize() || numberColumn - 1 >= index || numberRow < 1 || numberColumn < 1)
	{
		throw std::exception("Invalid index!");
	}
	MyString currStr(str);
	try
	{
		Helper::isValid(currStr);
		Types currStrType = Helper::determineType(currStr);
		if (currStrType == Types::string)
		{
			Helper::removeUselessSlashes(currStr);
		}
		rows[numberRow - 1][numberColumn - 1]->setValue(currStr);
	}
	catch (const std::invalid_argument& exe)
	{
		throw;
	}
}

//Gets the index of the row in a cell
static void getIndex(const MyString& str, size_t& index)
{	
	unsigned ind = 1;
	while (str[ind] != 'C')
	{
		index *= 10;
		index += (str[ind] - '0');
		ind++;
	}
}

//Gets the index of a column in a cell
static void getSecondIndex(const MyString& str, size_t& index)
{
	size_t ind = 1;
	while (str[ind] != 'C')
	{
		ind++;
	}
	++ind;
	while (str[ind] != '\0')
	{
		index *= 10;
		index += (str[ind] - '0');
		ind++;
	}
}

//checks if two cells are the same
static bool isTheSameCell(const MyString& currString, const MyString& checkStr)
{
	std::stringstream ss(checkStr.c_str());
	ss.ignore(2);
	MyString newStr;
	while (!ss.eof())
	{
		ss >> newStr;
		if (currString == newStr)
		{
			return false;
		}
	}
	return true;
}

void Table::getValueFromCell(MyString& str) const
{
	double resultCell = 0;

	size_t ind1 = 0, ind2 = 0;
	getIndex(str, ind1);
	getSecondIndex(str, ind2);
	MyString recursionBot(str);
	try
	{
		str = rows[ind1 - 1][ind2 - 1]->getString();
	}
	catch (const std::exception&)
	{
		str = "0";
	}
	if (!isTheSameCell(recursionBot, str))
	{
		throw std::exception("The cell you selected is the same. Please enter different value!");
	}
	if (Helper::isValidFormula(str))
	{
		Value* tempValue = valueFactory(str);
		calculateFormula(tempValue);
		str = tempValue->getString();
		delete tempValue;
	}
	else if (!Helper::isNumber(str))
	{
		str = "0";
	}
	
}

//Idea Taken From geeksforgeeks
MyString Table::infixToPostfix(const MyString& s, Vector<double>& doubleArr, Vector<char>& operations) const 
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
		if (Helper::isCell(currNum))
		{
			try
			{
				getValueFromCell(currNum);
			}
			catch (const std::exception& exe)
			{
				std::cout << exe.what() << std::endl;
				exit(0);
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
			if (currNum.length() == 0) //if currNum is empty, than add zero
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
	unsigned resultLength = result.length();
	for (size_t i = 0; i < resultLength; i++)
	{
		if (result[i] == '*' || result[i] == '+' || result[i] == '-' || result[i] == '^' || result[i] == '/')
		{
			operations.pushBack(result[i]);
		}
	}
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
			throw std::invalid_argument("Operation cannot be done. The divisor is equal to 0. ");
		}
		return num1 / num2;
	default:
		return -1;
	}
}

size_t Table::findIndOfOperation(const MyString& str, char op, size_t startIndex, size_t& indexUntilNow) const
{
	int counterSpaces = startIndex;
	unsigned strLength = str.length();
	for (size_t i = indexUntilNow; i <= strLength; i++)
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

void Table::changeTheValueOfFormula(double num, Value* value) const
{
	std::stringstream ss;
	ss << num;
	char buff[1024]{};
	ss.getline(buff, 1024);
	MyString strCurr(buff);
	value->setValue(strCurr);
}

void Table::calculateFormula(Value* value) const
{
	Vector<double> nums; //all numbers in the formula
	Vector<char> operations; //all operations in the formula
	MyString str = infixToPostfix(value->getString(), nums, operations);//form infix to postfix
	int indOp = 0;
	int reduceIndOp = 0;
	size_t indexUntilNow = 0;
	while (nums.getSize() != 1)
	{
		indOp = findIndOfOperation(str, operations[0], indOp, indexUntilNow); //gets the index of the operation in the vector
		double currRes = 0;
		try
		{
			currRes = getResult(operations[0], nums[indOp - reduceIndOp - 2], nums[indOp - reduceIndOp - 1]); //gets the result from the current cell
		}
		catch (const std::invalid_argument& exe)
		{
			std::cout << exe.what() << std::endl;
			value->setValue("ERROR");
			return;
		}
		
		nums.popAt(indOp - reduceIndOp - 2);
		nums.pushAt(currRes, indOp - reduceIndOp - 2);
		nums.popAt(indOp - reduceIndOp - 1);// remove the numbers, which have been used
		reduceIndOp += 2;
		operations.popAt(0); // removes the used operation
	}
	changeTheValueOfFormula(nums[0], value);//from formula to the actula value
}

//adds spaces for alignement
void Table::addSpaces(int conditionValue) const
{
	while (conditionValue != 0)
	{
		std::cout << " ";
		conditionValue--;
	}
}

//gets max number of values from all rows
unsigned Table::getMaxValueInRows() const
{
	unsigned maxValues = 0;
	unsigned rowsCount = rows.getSize();
	for (size_t i = 0; i < rowsCount; i++)
	{
		if (rows[i].getValuesCount() > maxValues)
		{
			maxValues = rows[i].getValuesCount();
		}
	}
	return maxValues;
}

void Table::printRow(const Row& row, Vector<int>& numberOfSpaces) const {
	size_t countValuesInRow = row.getValuesCount();
	if (row.getValuesCount() != 0)
	{
		std::cout << "| ";
	}
	for (size_t i = 0; i < countValuesInRow; i++)
	{
		int copyNumberOfSpaces = numberOfSpaces[i];
		int spacesTaken = row[i]->getString().length();
		int spacesLeftToPrint = copyNumberOfSpaces - spacesTaken;
		addSpaces(spacesLeftToPrint);
		std::cout << row[i]->getString();

		if (i == numberOfSpaces.getSize() - 1)
		{
			std::cout << " |";
			std::cout << std::endl;
			break;
		}
		std::cout << " | ";
	}
	for (size_t i = countValuesInRow + 1; i <= numberOfSpaces.getSize(); i++)
	{
		addSpaces(numberOfSpaces[i - 1]);
		if (i == numberOfSpaces.getSize())
		{
			std::cout << " |";
			std::cout << std::endl;
		}
		else
		{
			std::cout << " | ";
		}
	}
}

void Table::printTable() {
	unsigned maxValuesOnRow = getMaxValueInRows();
	Vector<int> numberOfSpaces(maxValuesOnRow);
	getMaxLengthFromEachColumn(numberOfSpaces);
	unsigned rowsCount = rows.getSize();
	for (size_t i = 0; i < rowsCount; i++)
	{
		printRow(rows[i], numberOfSpaces);
	}
}