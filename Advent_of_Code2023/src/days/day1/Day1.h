#pragma once
#include <array>
#include <string>

#include "../../parser/Parser.h"

class Day1
{
	static constexpr const char* InputFile = "resources/day1/input.txt";

	inline static const std::array<std::string, 9> digits = {
		"one", "two", "three", "four",
		"five", "six", "seven", "eight",
		"nine"
	};

	Parser parser;

public:
	Day1();

	int FindSumOfCalibrationValues() const;
};
