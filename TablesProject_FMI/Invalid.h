#pragma once
#include "Value.h"

class Invalid : public Value {
public:
	Invalid();
	Invalid(const MyString& str);
	Value* clone() const override;
};