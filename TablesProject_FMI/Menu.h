#pragma once
#include "Table.h"
#include <fstream>
#include "myVector.hpp"
#include <windows.h>
#include "GlobalConstants.h"

class Menu {
public:
	static unsigned StringToInt(const MyString& str);
	static void validateOption(MyString& option);
	static int mainMenu();
	static bool checkEmptyFile(std::fstream& myFile);
	static bool isOnlyDigits(const MyString& str);
	static void validateNewFileName(MyString& str);
	static void saveAs(Table& newTable);
	static void edit(Table& newTable);
	static void closeFile(std::fstream& fs);
	static void chooseAnOption(Table& newTable, int option, std::fstream& fs, const MyString& str);
	static void runProgram();
};