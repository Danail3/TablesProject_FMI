#pragma once
#include "Value.h"


class DoubleNum : public Value {
public:
	DoubleNum();
	DoubleNum(const MyString& str);
	Value* clone() const override;
};