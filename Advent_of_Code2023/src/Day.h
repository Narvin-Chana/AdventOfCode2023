#pragma once
#include <iostream>
#include <string>
#include "parser/Parser.h"
using namespace std;

template <int DayNumber>
struct Day
{
	std::string inputFile;
	Parser parser;
	std::string partOneDescriptor;
	std::string partTwoDescriptor;

	Day()
		: inputFile(std::format("resources/day{}/input.txt", DayNumber))
		, parser(inputFile)
	{}
	virtual ~Day() = default;

	std::string PartOne();
	std::string PartTwo();

	void ExecuteParts();
};

template <int DayNumber>
void Day<DayNumber>::ExecuteParts()
{
	std::cout << std::format("Day {}: \n", DayNumber);

	const std::string partOneResult = PartOne();
	std::cout << "\tPart One: " << (!partOneDescriptor.empty() ? partOneDescriptor + ": " : "") << partOneResult << '\n';

	const std::string partTwoResult = PartTwo();
	std::cout << "\tPart Two: " << (!partTwoDescriptor.empty() ? partTwoDescriptor + ": " : "") << partTwoResult << '\n';
}
