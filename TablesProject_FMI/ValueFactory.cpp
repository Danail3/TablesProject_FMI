#include "ValueFactory.h"

Value* valueFactory(const MyString& str)
{
	Types type = Helper::determineType(str);
	switch (type)
	{
	case Types::intNum:
		return new IntNum(str);
	case Types::doubleNum:
		return new DoubleNum(str);
	case Types::string:
		return new String(str);
	case Types::formula:
		return new Formula(str);
	case Types::empty:
		return new Empty(str);
	case Types::invalid:
		return new Invalid(str);
	}
	return nullptr;
}