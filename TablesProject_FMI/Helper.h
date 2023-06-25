#pragma once
#include "MyString.h"
#include "GlobalConstants.h"
#include "Value.h"

class Helper {
public:
	static bool isValidString(const MyString& str);
	static bool isValidFormula(const MyString& str);
	static bool isNumber(const MyString& str);
	static bool isDouble(const MyString& str);
	static bool isCell(const MyString& str);
	static bool isValid(MyString& str);
	static void removeSpaces(MyString& str);
	static Types determineType(const MyString& str);
	static void removeUselessSlashes(MyString& str);
};

