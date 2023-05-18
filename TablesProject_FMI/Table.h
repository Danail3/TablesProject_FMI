#pragma once
#include "Row.h"
#include "myVector.hpp"

class Table {
	Vector<Row> rows;
	
public:
	Table() = default;
	Table(Vector<Row> rows);

	size_t getRowsCount() const;
	size_t getCapacity() const;
	//void setRow(const Row& row, size_t index);

	void printTable() const;
	void exportDataFromFile(std::fstream& fs);
	void saveDataToFile(std::fstream& fs) const;

	void editCell(size_t numberRow, size_t numberColumn, const MyString& str);
};

