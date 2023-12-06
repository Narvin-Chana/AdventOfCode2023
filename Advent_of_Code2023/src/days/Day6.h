#pragma once

#include "../Day.h"

template <typename T>
struct BoatRace
{
	T time;
	T distance;

	T GetNumberOfWaysToWin() const
	{
		T numWays = 0;

		for (T i = 0; i < time; ++i)
		{
			if (i * (time - i) > distance)
				++numWays;
		}

		return numWays;
	}
};

inline std::string Day<6>::PartOne()
{
	partOneDescriptor = "Boat Races Multiplication Record";

	int totalNumberOfWaysMultiplied = 1;

	vector<string_view> times;
	Parser::Split(parser.GetLine(0).substr(9), times, " ", true);

	vector<string_view> distances;
	Parser::Split(parser.GetLine(1).substr(9), distances, " ", true);

	assert(times.size() == distances.size());

	for (int i = 0; i < static_cast<int>(times.size()); ++i)
	{
		BoatRace<int> race({Parser::GetNumberFromStringView<int>(times[i]), Parser::GetNumberFromStringView<int>(distances[i])});

		totalNumberOfWaysMultiplied *= race.GetNumberOfWaysToWin();
	}

	return to_string(totalNumberOfWaysMultiplied);
}

inline std::string Day<6>::PartTwo()
{
	partTwoDescriptor = "Boat Race Concatenation Record";

	vector<string_view> times;
	Parser::Split(parser.GetLine(0).substr(9), times, " ", true);

	vector<string_view> distances;
	Parser::Split(parser.GetLine(1).substr(9), distances, " ", true);

	auto concatenateAccumulationFunc = [](string b, const string_view s)
	{
		b += s;
		return b;
	};

	const uint64_t time = Parser::GetNumberFromStringView<uint64_t>(accumulate(times.begin(),
																			   times.end(),
																			   string{},
																			   concatenateAccumulationFunc
	));

	const uint64_t distance = Parser::GetNumberFromStringView<uint64_t>(accumulate(distances.begin(),
																				   distances.end(),
																				   string{},
																				   concatenateAccumulationFunc

	));

	return to_string(BoatRace<uint64_t>({time, distance}).GetNumberOfWaysToWin());
}
