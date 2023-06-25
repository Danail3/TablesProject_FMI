#include "Helper.h"
#include <sstream>

//removes slashes before " and the reversed slash
void Helper::removeUselessSlashes(MyString& str)
{
	unsigned lengthReducer = 0;
	unsigned strLength = str.length() - 1;
	for (size_t i = 1; i < strLength; i++)
	{
		char firstChar = str[i];
		char secondChar = str[i + 1];
		if ((firstChar == '\\' && secondChar == '\"') || (firstChar == '\\' && secondChar == '\\'))
		{
			unsigned newLength = str.length() - lengthReducer;
			for (size_t j = 1; j < newLength; j++)
			{
				str[i + j - 1] = str[i + j];
			}
			lengthReducer++;
		}
	}
	str = str.c_str();
}

static unsigned countSymbols(const MyString& str)
{
	unsigned counter = 0;
	unsigned strLength = str.length();
	for (size_t i = 0; i < strLength; i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			counter++;
		}
	}
	return counter;
}

//removes spaces before and after the string
void Helper::removeSpaces(MyString& str)
{
	int index = 0;
	while (str[index] == ' ')
	{
		index++;
	}
	int lengthWithoutSpaces = str.length() - index;
	for (size_t i = 0; i < lengthWithoutSpaces; i++)
	{
		str[i] = str[index + i];
	}
	if (index != 0)
	{
		str[lengthWithoutSpaces] = '\0';
		index = 0;
	}
	while (str[lengthWithoutSpaces - 1] == ' ')
	{
		str[lengthWithoutSpaces - 1] = '\0';
		--lengthWithoutSpaces;
	}
	str = str.c_str();
}


bool Helper::isCell(const MyString& str)// not static, because I am using it in table.cpp for calculating a formula
{
	int i = 2;
	bool cOccured = false;
	if (str[0] == 'R' && (str[1] >= '1' && str[1] <= '9'))
	{
		while (str[i] != '\0')
		{
			if ((str[i] < '0' || str[i] > '9') && str[i] != 'C')
			{
				return false;
			}
			if (str[i] == 'C')
			{
				cOccured = true;
			}
			i++;
		}
		if (!cOccured)
			return false;
		else
			return true;
	}
	else
		return false;
}

bool Helper::isDouble(const MyString& str)
{
	if (countSymbols(str) > 2 || countSymbols(str) == 0)
	{
		return false;
	}
	if (str.length() == countSymbols(str) || str.length() < 3)
	{
		return false;
	}
	if (str.length() >= 2 && countSymbols(str) == 2)
	{
		if (str[0] != '-' && str[0] != '+')
		{
			return false;
		}
		else
		{
			if (str[1] == '.' || str[str.length() - 1] == '.')
			{
				return false;
			}
			for (size_t i = 1; i < str.length(); i++)
			{
				if (str[i] == '.')
				{
					return true;
				}
			}
			return false;
		}
	}
	return true;
}

bool Helper::isNumber(const MyString& str)
{
	bool isNum = isDouble(str);
	if (isNum)
	{
		return true;
	}
	if (countSymbols(str) > 1)
	{
		return false;
	}
	if (str.length() == countSymbols(str))
	{
		return false;
	}

	if (countSymbols(str) == 1 && str[0] != '-' && str[0] != '+')
	{
		return false;
	}
	return true;
}

bool Helper::isValidString(const MyString& str)
{
	if (str[0] != '"' || str[str.length() - 1] != '"')
	{
		return false;
	}
	else
	{
		return true;
	}
	unsigned strLength = str.length() - 2;
	for (size_t i = 1; i < strLength; i++)
	{
		if (str[i] == '\"' && str[i - 1] != '\\')
		{
			return false;
		}
		else if (str[i] == '\\' && str[i - 1] != '\\' && (str[i + 1] != '\"' && str[i + 1] != '\\'))
		{
			return false;
		}
	}
}

bool Helper::isValidFormula(const MyString& str)
{
	std::stringstream line(str.c_str());
	char buff[64]{};
	bool isOperation = false;
	line >> buff;
	if (strcmp(buff, "=") != 0 || str[str.length() - 1] == '+' || str[str.length() - 1] == '-' || str[str.length() - 1] == '*' || str[str.length() - 1] == '/' || str[str.length() - 1] == '^')
	{
		return false;
	}
	else
	{
		while (true)
		{
			if (line.eof())
			{
				break;
			}
			line >> buff;
			if ((isNumber(buff) || isCell(buff)) && isOperation == false)
			{
				isOperation = true;
			}
			else if ((buff[0] == '+' || buff[0] == '-' || buff[0] == '*' || buff[0] == '/' || buff[0] == '^') && isOperation) {
				isOperation = false;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
}

bool Helper::isValid(MyString& str)
{
	removeSpaces(str);
	if (isNumber(str) || isValidFormula(str) || isValidString(str) || str == "")
	{
		return true;
	}
	throw std::invalid_argument(" is invalid data type!");
}

Types Helper::determineType(const MyString& str)
{
	if (isValidFormula(str))
	{
		return Types::formula;
	}
	else if (isValidString(str))
	{
		return Types::string;
	}
	else if (isDouble(str))
	{
		return Types::doubleNum;
	}
	else if (isNumber(str) && !isDouble(str))
	{
		return Types::intNum;
	}
	else if (str == "")
	{
		return Types::empty;
	}
	else
	{
		return Types::invalid;
	}
}