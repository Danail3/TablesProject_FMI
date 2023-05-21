#include "Value.h"
#include <sstream>

static unsigned countSymbols(const MyString& str)
{
	unsigned counter = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			counter++;
		}
	}
	return counter;
}

bool isCell(const MyString& str)// ne go pravq static, shtot mi trqq v table.cpp kat smqtam formulata
{
	int i = 2;
	bool cOccured = false;
	if (str[0] == 'R' && (str[1] >= '1' && str[1] <= '9')/* && str[2] == 'C'*/)
	{
		while (str[i] != '\0')/*) && (str[3] >= '0' && str[3] <= '9')*/
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

bool isDouble(const MyString& str)
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

bool isNumber(const MyString& str)
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


int tryParseToInt(const MyString& str)
{

	int result = 0;
	size_t index = 0;
	if (countSymbols(str) > 1)
	{
		return 0;
	}
	if (str.length() >= 2 && countSymbols(str) == 1)
	{
		if (str[0] == '-' || str[0] == '+')
		{
			index++;
		}
		else {
			return 0;
		}
	}

	for (index; index < str.length(); index++)
	{
		result *= 10;
		result += str[index] - '0';
	}
	if (str[0] == '-')
	{
		result *= (-1);
	}
	return result;
}

double tryParseToDouble(const MyString& str)
{
	double result = 0;
	int howManyDigitsAfterDot = 1;
	bool passedDot = false;
	size_t index = 0;
	if (countSymbols(str) == 0 || countSymbols(str) > 2)
	{
		return 0;
	}
	if (str.length() >= 4 && countSymbols(str) == 2)
	{
		if (str[0] == '+' || str[0] == '-')
		{
			index++;
		}
		else
		{
			return 0;
		}
	}

	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == '.')
		{
			passedDot = true;
			continue;
		}
		result *= 10;
		result += str[i];
		if (passedDot)
		{
			howManyDigitsAfterDot *= 10;
		}
	}
	if (str[0] == '-')
	{
		result *= (-1);
	}
	return (result / howManyDigitsAfterDot);
}

bool isValidString(const MyString& str)
{
	if (str[0] == '"' && str[str.length() - 1] == '"')
	{
		return true;
	}
	return false;
}

bool isValidFormula(const MyString& str)
{
	std::stringstream line(str.c_str());
	char buff[64]{};
	bool isOperation = false;
	line >> buff;
	if (strcmp(buff, "=") != 0)
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

bool isValid(MyString& str)
{
	removeSpaces(str);
	if (isNumber(str) || isValidFormula(str) || isValidString(str) || str == "")
	{
		return true;
	}
	throw std::invalid_argument(" is invalid data type!");
	//return false;
}

void Value::determineType()
{
	if (isValidFormula(str))
	{
		type = Types::formula;
	}
	else if (isValidString(str))
	{
		type = Types::string;
	}
	else if (isDouble(str))
	{
		type = Types::doubleNum;
	}
	else if (isNumber(str) && !isDouble(str))
	{
		type = Types::intNum;
	}
	else if (str == "")
	{
		type = Types::empty;
	}
	else
	{
		//str = "Invalid";
		type = Types::invalid;
		//throw std::invalid_argument("");
	}
}

void removeSpaces(MyString& str)
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
void Value::setValue(const MyString& str)
{
	MyString newStr(str);
	removeSpaces(newStr);
	/*try
	{
		isValid(str);
	}
	catch (const std::exception&)
	{
		throw std::invalid_argument("Invalid Argument!");
	}*/
	this->str = newStr;
	determineType();
}

const MyString& Value::getString() const
{
	return str;
}

Value::Value() : Value("") {};

Value::Value(const MyString& str)
{
	setValue(str);
}

Types Value::getType() const
{
	return type;
}