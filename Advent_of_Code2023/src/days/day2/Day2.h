#pragma once

#include "../../parser/Parser.h"


struct Bag
{
	int redCubes;
	int greenCubes;
	int blueCubes;

	[[nodiscard]] int GetPower() const noexcept
	{
		return redCubes * greenCubes * blueCubes;
	}
	bool operator==(const Bag& other) const
	{
		return redCubes == other.redCubes && greenCubes == other.greenCubes && blueCubes == other.blueCubes;
	}
};

class Day2
{
	static constexpr const char* InputFile = "resources/day2/input.txt";
public:
	Day2();

	int CountIDSumOfPossibleGames(const Bag& bag) const;
	int CountIDSumOfPowersOfMinimalSet() const;

private:
	Parser parser;
};
