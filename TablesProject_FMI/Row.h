#pragma once
#include "Value.h"
#include <fstream>
#include "myVector.hpp"

class Row {
	//size_t capacity = 1;

	Vector<Value> values;
	//Value* values = new Value[capacity];
	size_t valuesCount = 0;

	//void resize(unsigned newCap);
	//void copyFrom(const Row& other);
	//void moveFrom(Row&& other);
	//void free();

public:
	Row() = default;
	Row(const Vector<Value> newValues/*const Value* values*//*, size_t capacity*/, size_t valuesCount);

	//void resize(size_t newCap);

	void setValues(const Vector<Value> values/*const Value* values*//*, size_t capacity*/ ,size_t valuesCount);
	size_t getValuesCount() const; // ne se znae dali mi trqq
	void printRow() const; //shte mi trqq za priniraneto na tablicata
	const Vector<Value>& getValues() const;

	//Row& operator=(const Row& other);
	//Row(const Row& other);
	//~Row();

	//Row(Row&& other) noexcept;
	//Row& operator=(Row&& other) noexcept;
	void readRow(std::fstream& fs);
	void saveRow(std::fstream& fs) const;

	Value& operator[](int index);
	Value operator[](int index) const;
};
//void openFile(const MyString& name);

