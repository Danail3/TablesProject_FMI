#include "Table.h"
#include <fstream>


void Table::setRow(const Row& newRow, size_t index)
{
	rows[index] = newRow;
	//if (newRows == nullptr)
	//{
	//	throw std::invalid_argument("There are not any rows!"); //da vidq kvo sum zapisal za tva v Row
	//}
	
}

Table::Table(Vector<Row> newRows/*const Row* newRows*/, size_t rowsCount)
{
	this->rowsCount = rowsCount;
	//this->capacity = capacity;
	for (size_t i = 0; i < rowsCount; i++)
	{
		setRow(newRows[i], i);
	}
	//setRows(newRows, rowsCount);


}

//void Table::copyFrom(const Table& other)
//{
//	rowsCount = other.rowsCount;
//	//capacity = other.capacity;
//	rows = new Row[rowsCount];
//	for (size_t i = 0; i < rowsCount; i++)
//	{
//		rows[i] = other.rows[i];
//	}
//}
//
//void Table::moveFrom(Table&& other)
//{
//	rows = other.rows;
//	other.rows = nullptr;
//
//	//capacity = other.capacity;
//	//other.capacity = 0;
//
//	rowsCount = other.rowsCount;
//	other.rowsCount = 0;
//}
//
//void Table::free()
//{
//	delete[] rows;
//	rows = nullptr;
//	//capacity = 0;
//	rowsCount = 0;
//}
//
//Table::Table(const Table& other)
//{
//	copyFrom(other);
//}
//
//Table::Table(Table&& other) noexcept
//{
//	moveFrom(std::move(other));
//}
//
//Table& Table::operator=(Table&& other) noexcept
//{
//	if (this != &other)
//	{
//		free();
//		moveFrom(std::move(other));
//	}
//	return *this;
//}
//
//Table& Table::operator=(const Table& other)
//{
//	if (this != &other)
//	{
//		free();
//		copyFrom(other);
//	}
//	return *this;
//}
//
//Table::~Table()
//{
//	free();
//}
//
//void Table::resize(size_t newCap) {
//	Row* newRows = new Row[newCap];
//	for (size_t i = 0; i < rowsCount; i++)
//	{
//		newRows[i] = rows[i];
//	}
//	delete[] rows;
//	rows = newRows;
//	capacity = newCap;
//}

size_t Table::getRowsCount() const {
	return rowsCount;
}

//size_t Table::getCapacity() const {
//	return capacity;
//}

//Row* Table::getRows() const {
//	return rows;
//}

void Table::exportDataFromFile(std::fstream& fs)
{
	size_t index = 0;
	while (!fs.eof())
	{
		/*if (rowsCount == capacity)
		{
			resize(capacity * 2);
		}*/
		Row currRow;
		currRow.readRow(fs);
		rows.pushBack(currRow);
	}
	return;
}

void Table::saveDataToFile(std::fstream& fs) const 
{
	for (size_t i = 0; i < rows.getSize(); i++)
	{
		rows[i].saveRow(fs);
	}
}

void Table::editCell(size_t numberRow, size_t numberColumn, const MyString& str)
{
	if (numberRow > rows.getSize() || numberColumn > rows[numberRow].getValues().getSize())
	{
		throw std::invalid_argument("Invalid index!");
	}
	rows[numberRow][numberColumn].setValue(str);
}

//void Table::printTable() const {
//	//int* lengthArr = new int[rowsCount] {};
//
//}