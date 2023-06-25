#pragma once
#include "Value.h"

class IntNum : public Value {
public:
	IntNum();
	IntNum(const MyString& str);
	Value* clone() const override;
};