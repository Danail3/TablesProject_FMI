#pragma once
#include "Helper.h"

class Value {
	MyString str;
	Types type;
	void determineType();//trqq mi e tuka, shot kat suzdavam obekti i to go suzdava prez constuctor-a na value, koito mi polzva determine type

public:
	Value();
	Value(const MyString& str);
	virtual const MyString& getString() const;
	void setValue(const MyString& str);
	Types getType() const;

	virtual Value* clone() const = 0;
	virtual ~Value() = default;
};
