#include "Empty.h"
#include "Value.h"

Empty::Empty() : Value() {};

Empty::Empty(const MyString& str) : Value(str) {};

Value* Empty::clone() const {
	Value* newObj = new Empty(*this);
	return newObj;
}