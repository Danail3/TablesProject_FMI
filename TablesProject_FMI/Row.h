#pragma once
#include "Value.h"
#include <fstream>
#include "myVector.hpp"

class Row {
	Value** values;
	size_t valuesCount;
	size_t capacity;

	void addValue(const MyString& str);
	bool checkForMissedCommas(const MyString& str, char& symbolForComma);
	bool checkIfFormulaExists(std::stringstream& ss, unsigned& begInd, unsigned& endInd);

	void free();
	void copyFrom(const Row& other);
	void moveFrom(Row&& other);
	void resize();

public:
	Row();
	Row(const Row& other);
	Row& operator=(const Row& other);
	~Row();
	Row(Row&& other) noexcept;
	Row& operator=(Row&& other) noexcept;

	const size_t getValuesCount() const;

	void readRow(std::fstream& fs, size_t& rowIndex);
	void saveRow(std::fstream& fs) const;

	Value* operator[](int index);
	const Value* operator[](int index) const;
};

