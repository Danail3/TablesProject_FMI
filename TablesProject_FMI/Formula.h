#pragma once
#include "Value.h"

class Formula : public Value {
public:
	Formula();
	Formula(const MyString& str);
	Value* clone() const override;
};
