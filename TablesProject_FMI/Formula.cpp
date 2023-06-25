#include "Formula.h"
#include "Value.h"

Formula::Formula() : Value() {};

Formula::Formula(const MyString& str) : Value(str) {};

Value* Formula::clone() const {
	Value* newObj = new Formula(*this);
	return newObj;
}