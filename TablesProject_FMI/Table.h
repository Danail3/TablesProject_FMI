#pragma once
#include "Row.h"
#include "myVector.hpp"

class Table {
	Vector<Row> rows;
	
	//double calculateFormula(Value& currValue, double& result) const;
	

	void getValueFromCell(MyString& str) const;
	MyString infixToPostfix(const MyString& s, Vector<double>& doubleArr, Vector<char>& operations) const;
	size_t findIndOfOperation(const MyString& str, char op, size_t startIndex, size_t& indexUntilNow) const;
	double getResult(char ch, double num1, double num2) const;
public:
	Table() = default;
	Table(Vector<Row>& rows);

	size_t getRowsCount() const;
	size_t getCapacity() const;
	//void setRow(const Row& row, size_t index);
	//double ConvertTheCellToNumber(Value& currValue) const;
	const MyString& convertTheFromulaIntoArray(const MyString& str) const;
	double calculateFormula(Value& value) const;

	void printTable() const;
	void exportDataFromFile(std::fstream& fs);
	void saveDataToFile(std::fstream& fs) const;

	void editCell(size_t numberRow, size_t numberColumn, const MyString& str);
};

