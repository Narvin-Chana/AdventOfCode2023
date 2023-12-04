#pragma once
#include "../../parser/Parser.h"

class Day3
{
	static constexpr const char* InputFile = "resources/day3/input.txt";
public:
	Day3();

	int GetSumOfPartNumbers() const;
	int GetSumOfGearRatios() const;

private:
	Parser parser;

	static bool DoesLineSubstringContainSymbol(std::string_view line, size_t firstPos, size_t lastPos);
};

