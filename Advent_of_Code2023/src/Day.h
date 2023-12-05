#pragma once
#include <iostream>
#include <string>
#include <chrono>
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
	std::cout << format("Day {}: \n", DayNumber);

	auto [partOneResult, dt1] = Test([&] { return PartOne(); });
	std::cout << "\tPart One: " << (!partOneDescriptor.empty() ? partOneDescriptor + ": " : "") << partOneResult << " in " << chrono::duration_cast<chrono::microseconds>(dt1) << '\n';

	auto [partTwoResult, dt2] = Test([&] { return PartTwo(); });
	std::cout << "\tPart Two: " << (!partTwoDescriptor.empty() ? partTwoDescriptor + ": " : "") << partTwoResult << " in " << chrono::duration_cast<chrono::microseconds>(dt2) << '\n';
}
