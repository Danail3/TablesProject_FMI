#include "Row.h"

//void Row::resize(unsigned newCap)
//{
//	Value* newValues = new Value[newCap];
//	for (size_t i = 0; i < valuesCount; i++)
//	{
//		newValues[i] = values[i];
//	}
//	delete[] values;
//	values = newValues;//Tuka ne trqq triq, nali?
//	capacity = newCap;
//}

void Row::setValues(const Vector<Value> newValues/*Value* newValues*//*, size_t capacity*/, size_t valuesCount)
{
	if (newValues.getSize() == 0)
	{
		throw std::invalid_argument("There are not any values!");//Kato catch-na greshkata da ne go pravi nishto toq red, t.e da ne go ostavq dori i prazen
	}
	//values = new Value[capacity];
	for (size_t i = 0; i < valuesCount; i++)
	{
		values[i] = newValues[i];
	}
}

Row::Row(const Vector<Value> newValues/*const Value* newValues*//*, size_t capacity*/, size_t valuesCount)
{
	setValues(newValues ,valuesCount);
	//this->capacity = capacity;
	this->valuesCount = valuesCount;
}

//void Row::copyFrom(const Row& other)
//{
//	valuesCount = other.valuesCount;
//	//capacity = other.capacity;
//	values = new Value[valuesCount];
//	for (size_t i = 0; i < valuesCount; i++)
//	{
//		values[i] = other.values[i];
//	}
//}

//void Row::moveFrom(Row&& other)
//{
//	values = other.values;
//	other.values = nullptr;
//
//	capacity = other.capacity;
//	other.capacity = 0;
//
//	valuesCount = other.valuesCount;
//	other.valuesCount = 0;
//}
//
//void Row::free()
//{
//	delete[] values;
//	values = nullptr;
//	capacity = 0;
//	valuesCount = 0;
//}
//
//Row::Row(const Row& other)
//{
//	copyFrom(other);
//}
//
//Row::Row(Row&& other) noexcept
//{
//	moveFrom(std::move(other));
//}
//
//Row& Row::operator=(Row&& other) noexcept
//{
//	if (this != &other)
//	{
//		free();
//		moveFrom(std::move(other));
//	}
//	return *this;
//}
//
//Row& Row::operator=(const Row& other)
//{
//	if (this != &other)
//	{
//		free();
//		copyFrom(other);
//	}
//	return *this;
//}
//
//Row::~Row()
//{
//	free();
//}

const Vector<Value>& Row::getValues() const {
	return values;
}

size_t Row::getValuesCount() const
{
	return valuesCount;
}

//void Row::resize(size_t newCap) {
//	Value* newValues = new Value[newCap];
//	for (size_t i = 0; i < valuesCount; i++)
//	{
//		newValues[i] = values[i];
//	}
//	delete[] values;
//	values = newValues;
//	capacity = newCap;
//}
void Row::readRow(std::fstream& fs)
{
	const static int MAX_LENGTH_ROW = 1024;
	char buff[MAX_LENGTH_ROW]{};
	fs.getline(buff, MAX_LENGTH_ROW);//Ne moga da vkaram myString tuka
	std::stringstream ss(buff);

	while (!ss.eof())
	{
		/*if (valuesCount == capacity)
		{
			resize(2 * capacity);
		}*/
		size_t& valuesCount = this->valuesCount;
		char currWord[MAX_LENGTH_ROW]{};
		ss.getline(currWord, MAX_LENGTH_ROW, ',');
		Value currValue(currWord);
		values.pushBack(std::move(currValue));
		valuesCount++;
		//values[valuesCount++].setValue(currWord);
		std::cout << values[valuesCount - 1].getString();
	}
}

void Row::saveRow(std::fstream& fs) const 
{
	for (size_t i = 0; i < values.getSize(); i++)
	{
		if (i == values.getSize() - 1)
			fs << values[i].getString() << std::endl;
		else
			fs << values[i].getString() << ", ";
	}
}

Value& Row::operator[](int index) {
	return values[index];
}

Value Row::operator[](int index) const {
	return values[index];
}