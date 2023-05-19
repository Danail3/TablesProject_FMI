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

void Table::getValueFromCell(MyString& str) const
{
	double resultCell = 0;
	int ind1 = str[1] - '0';
	int ind2 = str[3] - '0';
	str = rows[ind1 - 1][ind2 - 1].getString();
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
	std::cout << result << std::endl;
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

double Table::calculateFormula(Value& value) const
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
		double currRes = getResult(operations[0], nums[indOp - reduceIndOp - 2], nums[indOp - reduceIndOp - 1]);
		nums.popAt(indOp - reduceIndOp - 2);
		nums.pushAt(currRes, indOp - reduceIndOp - 2);
		nums.popAt(indOp - reduceIndOp - 1);

		for (size_t i = 0; i < nums.getSize(); i++)
		{
			std::cout << nums[i];
		}
		std::cout << std::endl;
		reduceIndOp += 2;
		operations.popAt(0);
		for (size_t i = 0; i < operations.getSize(); i++)
		{
			std::cout << operations[i];
		}
		std::cout << std::endl;

	}
	return nums[0];
}

void Table::printTable() const {
	//int* lengthArr = new int[rowsCount] {};

}