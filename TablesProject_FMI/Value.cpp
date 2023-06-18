#include "Value.h"
#include <sstream>

void Value::determineType()
{
	if (Helper::isValidFormula(str))
	{
		type = Types::formula;
	}
	else if (Helper::isValidString(str))
	{
		type = Types::string;
	}
	else if (Helper::isDouble(str))
	{
		type = Types::doubleNum;
	}
	else if (Helper::isNumber(str) && !Helper::isDouble(str))
	{
		type = Types::intNum;
	}
	else if (str == "")
	{
		type = Types::empty;
	}
	else
	{
		type = Types::invalid;
	}
}


void Value::setValue(const MyString& str)
{
	MyString newStr(str);
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
