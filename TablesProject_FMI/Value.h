#pragma once
#include "GlobalConstants.h"
//#include "MyString.h"

class Value {
	MyString str;
	Types type;

	

	void determineType();
public:

	

	Value();
	Value(const MyString& str);
	const MyString& getString() const;
	void setValue(const MyString& str);

	double calculateFormula() const;

	Types getType() const;
};

int tryParseToInt(const MyString& str);
double tryParseToDouble(const MyString& str);
bool isValidString(const MyString& str); //Tiq mai ne trqq sa mi v klasa
bool isValidFormula(const MyString& str); //
bool isNumber(const MyString& str); //
bool isDouble(const MyString& str); //
bool isCell(const MyString& str); //
bool isValid(MyString& str);
void removeSpaces(MyString& str);

