#include "Row.h"

void Row::setValues(const Vector<Value> newValues)
{
	if (newValues.getSize() == 0)
	{
		throw std::invalid_argument("There are not any values!");//Kato catch-na greshkata da ne go pravi nishto toq red, t.e da ne go ostavq dori i prazen
	}
	values = newValues;
}

Row::Row(const Vector<Value> newValues)
{
	setValues(newValues);// kato napisha std::move, to mi kazva, che ne trqq da go polzvam na const
	//ako go polzvam, to v setValues pak trqq da ne e const, za da prilagam move=
}

const Vector<Value>& Row::getValues() const {
	return values;
}

void Row::readRow(std::fstream& fs)
{
	const static int MAX_LENGTH_ROW = 1024;
	char buff[MAX_LENGTH_ROW]{};
	fs.getline(buff, MAX_LENGTH_ROW);//Ne moga da vkaram myString tuka
	std::stringstream ss(buff);

	while (!ss.eof())
	{
		char currWord[MAX_LENGTH_ROW]{};
		ss.getline(currWord, MAX_LENGTH_ROW, ',');
		Value currValue(currWord);
		values.pushBack(std::move(currValue));
		std::cout << values[values.getSize() - 1].getString();
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