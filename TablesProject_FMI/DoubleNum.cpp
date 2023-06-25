#include "DoubleNum.h"
#include "Value.h"

DoubleNum::DoubleNum() : Value() {};

DoubleNum::DoubleNum(const MyString& str) : Value(str) {};

Value* DoubleNum::clone() const {
	Value* newObj = new DoubleNum(*this);
	return newObj;
}