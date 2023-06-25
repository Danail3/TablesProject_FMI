#include "Menu.h"

//Using MSVC compiler

unsigned Menu::StringToInt(const MyString& str)
{
	unsigned result = 0;
	unsigned stringLength = str.length();
	for (size_t i = 0; i < stringLength; i++)
	{
		unsigned currDigit = str[i] - '0';
		result = result * 10 + currDigit;
	}
	return result;
}

void Menu::validateOption(MyString& option)
{
	while ((option.length() != 1) || (option[0] - '0' <= 0 || option[0] - '0' >= 8))
	{
		std::cout << "The number must be between 1 and 7: ";
		std::cin >> option;
		std::cin.ignore();
	}
}

int Menu::mainMenu()
{
	std::cout << "-------------------" << std::endl;
	std::cout << "1 - Open file" << std::endl;
	std::cout << "2 - Close file" << std::endl;
	std::cout << "3 - Save file" << std::endl;
	std::cout << "4 - Save file as" << std::endl;
	std::cout << "5 - Edit cell" << std::endl;
	std::cout << "6 - Print table" << std::endl;
	std::cout << "7 - Exit program" << std::endl;
	std::cout << "-------------------" << std::endl;

	std::cout << "Choose an option: ";
	MyString optionStr;
	std::cin >> optionStr;
	std::cin.ignore();
	validateOption(optionStr);
	int optionInt = optionStr[0] - '0';
	return optionInt;

}

bool Menu::checkEmptyFile(std::fstream& myFile)
{
	int currPos = myFile.tellg();
	MyString ch;
	myFile >> ch;
	if (ch[0] == '\0')
	{
		myFile.seekg(currPos);
		return true;
	}
	myFile.seekg(currPos);
	return false;
}

bool Menu::isOnlyDigits(const MyString& str)
{
	if (str[0] == '-')
	{
		std::cout << "The number must be positive!" << std::endl;
		return false;
	}
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			std::cout << "Must contain only digits!" << std::endl;
			return false;
		}
	}
	return true;
}

void Menu::validateNewFileName(MyString& str)
{
	static const int MAX_LENGTH_FILE_NAME = 1024;
	char newFileName[MAX_LENGTH_FILE_NAME]{};
	std::cout << "Enter the name of the new file (.txt only): ";
	std::cin.getline(newFileName, MAX_LENGTH_FILE_NAME);
	str = newFileName;

	while (str.substr(str.length() - 4, 4) != ".txt")
	{
		std::cout << "The file name must have \".txt\" extension" << std::endl;
		std::cin.getline(newFileName, MAX_LENGTH_FILE_NAME);
		str = newFileName;
	}
}

void Menu::saveAs(Table& newTable)
{
	MyString newFileNameStr;
	validateNewFileName(newFileNameStr);
	std::fstream newFile(newFileNameStr.c_str(), std::ios::out);
	if (!newFile.is_open())
	{
		std::cout << "Could not open file!" << std::endl;
		Sleep(1000);
		system("cls");
		return;
	}
	newTable.saveDataToFile(newFile);
	newFile.close();
	std::cout << "File saved as " << newFileNameStr << std::endl;
	Sleep(1000);
	system("cls");
}

void Menu::edit(Table& newTable)
{
	static const int MAX_LENGTH_CHANGE = 1024;
	MyString columnNum;
	unsigned numColumn;
	MyString rowNum;
	unsigned numRow;
	char buffEdit[MAX_LENGTH_CHANGE]{};
	std::cout << "Enter number of a column: ";
	std::cin >> columnNum;
	std::cin.ignore();
	while (!isOnlyDigits(columnNum))
	{
		std::cout << "Enter number of a column: ";
		std::cin >> columnNum;
		std::cin.ignore();
	}
	numColumn = StringToInt(columnNum);
	std::cout << "Enter number of a row: ";
	std::cin >> rowNum;
	std::cin.ignore();
	while (!isOnlyDigits(rowNum))
	{
		std::cout << "Enter number of a row: ";
		std::cin >> rowNum;
		std::cin.ignore();
	}
	numRow = StringToInt(rowNum);
	std::cout << "Enter what you want to change it to: ";
	std::cin.getline(buffEdit, MAX_LENGTH_CHANGE);
	MyString editStr(buffEdit);
	try
	{
		newTable.editCell(numRow, numColumn, editStr);
		std::cout << "Cell edited successfully!" << std::endl;
	}
	catch (const std::invalid_argument& exe)
	{
		std::cout << editStr.c_str() << exe.what() << std::endl;
	}
	catch (const std::exception& exe)
	{
		std::cout << "Invalid Index!" << std::endl;
	}
}

void Menu::closeFile(std::fstream& fs)
{
	char answer[1024]{};
	fs.close();
	std::cout << "File closed successfully!" << std::endl;
	Sleep(2000);
	system("cls");
	std::cout << "Do you want to exit the program - yes/no" << std::endl;
	std::cin.getline(answer, 1024);
	if (strcmp(answer, "yes") == 0)
	{
		std::cout << "Thank you for using our program!" << std::endl;
		exit(0);
	}
	std::cout << "You must open a new file, if you want to proceed with the actions!" << std::endl;
}

void Menu::chooseAnOption(Table& newTable, int option, std::fstream& fs, const MyString& str)
{
	switch (option)
	{
	case 1:
		std::cout << "File already opened!" << std::endl;
		Sleep(2000);
		system("cls");
		break;
	case 2:
		closeFile(fs);
		break;
	case 3:
		fs.close();
		fs.open(str.c_str(), std::ios::in | std::ios::out | std::ios::trunc);
		newTable.saveDataToFile(fs);
		std::cout << "File saved successfully!" << std::endl;
		Sleep(2000);
		system("cls");
		break;
	case 4:
		saveAs(newTable);
		break;
	case 5:
		edit(newTable);
		Sleep(2000);
		system("cls");
		break;
	case 6:
		newTable.printTable();
		system("pause");
		system("cls");
		break;
	case 7:
		fs.close();
		std::cout << "File closed successfully!" << std::endl;
		std::cout << "Thank you for using our platform!";
		exit(0);
		break;
	default:
		break;
	}
}

void Menu::runProgram()
{
	int key = 0;
	key = mainMenu();
	MyString fileName;
	while (key != 1 && key != 7)
	{
		std::cout << "You must open a file first!" << std::endl;
		Sleep(1000);
		system("cls");
		key = mainMenu();
	}
	if (key == 7)
	{
		std::cout << "Thank you for using our platform!" << std::endl;
		return;
	}
	while (true)
	{
		std::cout << "Enter the name of the file you want to open: ";
		std::cin >> fileName;
		std::cin.ignore();
		std::fstream myFile(fileName.c_str(), std::ios::in | std::ios::out | std::ios::_Nocreate);

		if (checkEmptyFile(myFile))
		{
			std::cout << "Such file does not exist!" << std::endl;
			Sleep(1000);
			system("cls");
			continue;
		}

		Table newTable;
		newTable.exportDataFromFile(myFile);

		int option = mainMenu();

		while (option < 8)
		{
			chooseAnOption(newTable, option, myFile, fileName);
			if (option == 2)
			{
				break;
			}
			option = mainMenu();
		}
	}
}