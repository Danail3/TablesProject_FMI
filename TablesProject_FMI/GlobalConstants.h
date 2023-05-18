#pragma once
#include <sstream>
#include <fstream>
#include "MyString.h"

enum class Types {
	intNum,
	doubleNum,
	string,
	formula,
	empty,
	invalid
};

//std::fstream& openFile(const MyString& name)
//{
//	std::fstream myFile(name.c_str(), std::ios::in | std::ios::out | std::ios::app);
//	//fs.open(name.c_str());
//	if (!myFile.is_open())
//	{
//		throw std::exception("File did not open!"); //Tuka moje da trqq da throw-na
//	}
//	return myFile;
//}

//void closeFile(std::fstream& fs)
//{
//	fs.close();
//}
//
//void saveFile(std::fstream& fs)
//{
//
//}
//
//void saveFileAs(std::fstream& fs)
//{
//
//}
//
//void exitTheProgram()
//{
//	exit(0);
//}
