#pragma once
#include "Row.h"
#include "myVector.hpp"
//#include <fstream>

class Table {
	//size_t capacity = 1;
	Vector<Row> rows;
	//Row* rows = new Row[capacity];//Tva nz dali e mn vqrno
	size_t rowsCount = 0;
	
	/*void copyFrom(const Table& other);
	void moveFrom(Table&& other);
	void free();*/
public:
	//Da chhekna kude trqq ima capacity
	Table() = default;
	Table(Vector<Row> rows/*const Row* rows*/, size_t rowsCount);

	//void resize(size_t newCap);

	Row* getRows() const; //Tva po-dobre da go nqma
	size_t getRowsCount() const;
	size_t getCapacity() const;
	void setRow(const Row& row, size_t index);
	

	//Table& operator=(const Table& other);
	//Table(const Table& other);
	//~Table();

	//Table(Table&& other) noexcept;
	//& operator=(Table&& other) noexcept;

	void printTable() const;
	void exportDataFromFile(std::fstream& fs);
	void saveDataToFile(std::fstream& fs) const;

	void editCell(size_t numberRow, size_t numberColumn, const MyString& str);
};

