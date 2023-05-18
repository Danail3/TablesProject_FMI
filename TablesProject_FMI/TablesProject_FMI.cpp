//#include <iostream>
//#include "GlobalConstants.h"
//#include "Value.h"
#include "Table.h"
#include <fstream>

int main()
{
	
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
