#include "Row.h"
#include "ValueFactory.h"

void Row::free()
{
	for (size_t i = 0; i < valuesCount; i++)
	{
		delete values[i];
	}
	delete[] values;
}

void Row::copyFrom(const Row& other)
{
	values = new Value * [other.capacity];
	valuesCount = other.valuesCount;
	capacity = other.capacity;

	for (size_t i = 0; i < valuesCount; i++)
		values[i] = other.values[i]->clone();
}

void Row::moveFrom(Row&& other)
{
	valuesCount = other.valuesCount;
	capacity = other.capacity;

	values = other.values;
	other.values = nullptr;

	other.valuesCount = other.capacity = 0;
}

void Row::resize()
{
	Value** newCollection = new Value * [capacity *= 2];
	for (size_t i = 0; i < valuesCount; i++)
	{
		newCollection[i] = values[i];
	}
	delete[] values;
	values = newCollection;
}

Row::Row()
{
	capacity = 8;
	valuesCount = 0;
	values = new Value * [capacity];
}

Row::Row(const Row& other)
{
	copyFrom(other);
}

Row& Row::operator=(const Row& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Row::~Row()
{
	free();
}

Row::Row(Row&& other) noexcept {
	moveFrom(std::move(other));
}

Row& Row::operator=(Row&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

bool Row::checkIfFormulaExists(std::stringstream& ss, unsigned& begInd, unsigned& endInd)
{
	MyString result;
	bool exists = false;
	bool firstOccurance = true;
	while (!ss.eof())
	{
		char buff[1024]{};
		ss >> buff;
		result += buff;
		if (strcmp(buff, "=") == 0)
		{
			if (firstOccurance)
			{
				firstOccurance = false;
				begInd = result.length() - 1;
			}
			else {
				break;

			}
		}
		if (Helper::isValidFormula(result))
		{
			endInd = begInd + result.length() - 1;
			exists = true;
		}
		result += ' ';
	}
	return exists;
}

//checks for missed commas in file
bool Row::checkForMissedCommas(const MyString& str, char& symbolForComma)
{
	std::stringstream ss(str.c_str());
	char buff[1024];
	MyString result;
	unsigned begFormula = 0;
	unsigned endFormula = 0;
	bool formulaExists = checkIfFormulaExists(ss, begFormula, endFormula);
	if (formulaExists && endFormula != str.length() - 1)
	{
		symbolForComma = str[endFormula];
		throw std::exception("Missed comma after ");
	}
	ss.seekg(0, std::ios::beg);
	while (!ss.eof())
	{
		ss.getline(buff, 1024, ' ');
		MyString currStr(buff);
		bool isValidValue;
		try
		{
			result += currStr;
			isValidValue = Helper::isValid(result);
			result += ' ';
		}
		catch (const std::exception& exe)
		{
			isValidValue = false;
		}
		if (isValidValue)
		{
			symbolForComma = currStr[currStr.length() - 1];
			throw std::exception("Missed comma after ");
		}
	}

}

const size_t Row::getValuesCount() const {
	return valuesCount;
}

void Row::addValue(const MyString& str)
{
	if (valuesCount == capacity)
		resize();
	values[valuesCount++] = valueFactory(str);
}

void Row::readRow(std::fstream& fs, size_t& rowIndex)
{
	const static int MAX_LENGTH_ROW = 1024;
	char buff[MAX_LENGTH_ROW]{};
	fs.getline(buff, MAX_LENGTH_ROW);//can't insert MyString in getline
	std::stringstream ss(buff);
	size_t columnIndex = 0;

	while (!ss.eof())
	{
		columnIndex++;
		char currWord[MAX_LENGTH_ROW]{};
		ss.getline(currWord, MAX_LENGTH_ROW, ',');
		char symbolForComma;
		MyString currStr(currWord);

		try
		{
			Helper::isValid(currStr);
			strcpy(currWord, currStr.c_str());
		}
		catch (const std::exception&)
		{
			try
			{
				checkForMissedCommas(currStr, symbolForComma);
			}
			catch (const std::exception& exe)
			{
				std::cout << exe.what() << symbolForComma << std::endl;
				char answer;
				do
				{
					std::cout << "Do you want to continue? - y/n" << std::endl;
					std::cin >> answer;
				} while (answer != 'y' && answer != 'n');

				if (answer == 'n')
				{
					exit(0);
				}
			}
			std::cout << "Error: row " << rowIndex << ", col " << columnIndex << ", " << currWord << " is unknown data type!" << std::endl;
			strcpy(currWord, "Invalid");

		}
		addValue(currWord);
	}
}

void Row::saveRow(std::fstream& fs) const
{
	for (size_t i = 0; i < valuesCount; i++)
	{
		if (i == valuesCount - 1)
			fs << values[i]->getString();
		else
			fs << values[i]->getString() << ", ";
	}
	fs.flush();
}

Value* Row::operator[](int index) {
	return values[index];
}

const Value* Row::operator[](int index) const {
	return values[index];
}