#pragma once
#include <iostream>
#include <string>
#include <chrono>

#include "color/ColorOutput.h"
#include "parser/Parser.h"
using namespace std;

template <class F, class... Args>
auto Test(F f, Args&&... args)
{
	auto pre = chrono::high_resolution_clock::now();
	auto res = f(std::forward<Args>(args)...);
	auto post = chrono::high_resolution_clock::now();
	return pair{res, post - pre};
}

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
	std::cout << ColorOutput(format("Day {}: \n", DayNumber), ColorTable::CYAN);

	auto [partOneResult, dt1] = Test([&] { return PartOne(); });
	std::cout << ColorOutput("\tPart One: ", ColorTable::BLUE) << (!partOneDescriptor.empty() ? partOneDescriptor + ": " : "") << ColorOutput(partOneResult, ColorTable::GREEN) << " in " << ColorOutput(to_string(chrono::duration_cast<chrono::microseconds>(dt1).count()) + "ms", ColorTable::RED) << '\n';

	auto [partTwoResult, dt2] = Test([&] { return PartTwo(); });
	std::cout << ColorOutput("\tPart Two: ", ColorTable::BLUE) << (!partTwoDescriptor.empty() ? partTwoDescriptor + ": " : "") << ColorOutput(partTwoResult, ColorTable::GREEN) << " in " << ColorOutput(to_string(chrono::duration_cast<chrono::microseconds>(dt2).count()) + "ms", ColorTable::RED) << '\n';
}
