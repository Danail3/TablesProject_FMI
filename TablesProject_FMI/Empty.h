#pragma once
#include "Value.h"

class Empty : public Value {
public:
	Empty();
	Empty(const MyString& str);
	Value* clone() const override;
};