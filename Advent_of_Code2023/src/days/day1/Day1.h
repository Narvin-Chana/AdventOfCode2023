#pragma once
#include <array>
#include <string>

#include "../../parser/Parser.h"

static constexpr const char* InputFile = "resources/day1/input.txt";

class Day1
{
	inline static const std::array<std::string, 9> digits = {
		"one", "two", "three", "four",
		"five", "six", "seven", "eight",
		"nine"
	};

	Parser parser;

public:
	Day1();

	std::vector<char> FindAllNumbersInAString(std::string_view line) const;
	int FindSumOfCalibrationValues() const;
};
