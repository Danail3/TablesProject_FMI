//#include <iostream>
//#include "GlobalConstants.h"
//#include "Value.h"
#include "Table.h"
#include <fstream>
#include "myVector.hpp"

int main()
{
	Value value2("2");
	Value value3("3");
	Value value4("4");
	Value value5("5");
	Value value6("6");
	Vector<Value> surr{5};
	surr.pushBack(value6);
	surr.pushBack(value5);
	surr.pushBack(value4);
	surr.pushBack(value3);
	surr.pushBack(value2);
	Row newRow(surr);
	Row newRow1(newRow);
	Vector<Row> rows{2};
	rows.pushBack(newRow);
	rows.pushBack(newRow1);
	Table table(rows);

	const char* name = "test.txt";
	std::fstream myFile(name, std::ios::in | std::ios::out | std::ios::app);
	Table myTable; 
	myTable.exportDataFromFile(myFile);
	std::fstream NOVO("NOVTESTAHAH.txt", std::ios::in | std::ios::out | std::ios::app);
	myTable.saveDataToFile(NOVO);
	myTable.editCell(1, 0, "136");
	myTable.editCell(1, 1, "136");
	myTable.saveDataToFile(NOVO);
}
