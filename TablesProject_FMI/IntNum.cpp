#include "IntNum.h"

IntNum::IntNum() : Value() {};

IntNum::IntNum(const MyString& str) : Value(str) {};

Value* IntNum::clone() const {
	Value* newObj = new IntNum(*this);
	return newObj;
}
