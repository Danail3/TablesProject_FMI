#pragma once
#include "Value.h"
#include <fstream>
#include "myVector.hpp"

class Row {
	Vector<Value> values;

public:
	Row() = default;
	Row(const Vector<Value> newValues);

	void setValues(const Vector<Value> values);
	void printRow() const; //shte mi trqq za priniraneto na tablicata
	const Vector<Value>& getValues() const;

	void readRow(std::fstream& fs);
	void saveRow(std::fstream& fs) const;

	Value& operator[](int index);
	Value operator[](int index) const; //tuka nz dali trqq da e taka
};
//void openFile(const MyString& name);

