#pragma once
#include "Row.h"
#include "myVector.hpp"
#include "ValueFactory.h"

class Table {
	Vector<Row> rows;
	
	void changeTheValueOfFormula(double num, Value* value) const;
	void getValueFromCell(MyString& str) const;
	MyString infixToPostfix(const MyString& s, Vector<double>& doubleArr, Vector<char>& operations) const;
	size_t findIndOfOperation(const MyString& str, char op, size_t startIndex, size_t& indexUntilNow) const;
	double getResult(char ch, double num1, double num2) const;
	void fillArrayWithLenghtOfEachRow(Row& row, Vector<int>& arr) const;
	void getMaxLengthFromEachColumn(Vector<int>& arr);
	unsigned getMaxValueInRows() const;
	void addSpaces(int conditionValue) const;
	void printRow(const Row& row, Vector<int>& numberOfSpaces) const;

public:
	Table() = default;
	void calculateFormula(Value* value) const;

	void printTable();
	void exportDataFromFile(std::fstream& fs);
	void saveDataToFile(std::fstream& fs) const;

	void editCell(size_t numberRow, size_t numberColumn, const MyString& str);
};

