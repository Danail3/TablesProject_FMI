#include "Table.h"
#include <fstream>

Table::Table(Vector<Row> newRows)
{
	size_t sizeOfVector = newRows.getSize();
	if (sizeOfVector == 0)
	{
		throw std::invalid_argument("There are not any values!");
	}
	for (size_t i = 0; i < sizeOfVector; i++)
	{
		rows.pushBack(std::move(newRows[i]));//pravilno li e da e move
		//setRow(newRows[i], i);
	}
}

void Table::exportDataFromFile(std::fstream& fs)
{
	size_t index = 0;
	while (!fs.eof())
	{
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
	int index = rows[numberRow].getValues().getSize();
	if (numberRow > rows.getSize() || numberColumn > index)
	{
		throw std::invalid_argument("Invalid index!");
	}
	rows[numberRow][numberColumn].setValue(str);
}

//void Table::printTable() const {
//	//int* lengthArr = new int[rowsCount] {};
//
//}