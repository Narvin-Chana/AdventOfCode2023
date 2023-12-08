#pragma once

#include "../Day.h"

struct RepeatingSequence
{
	int pos;
	string_view seq;

	RepeatingSequence(const string_view vec)
		: pos{0}, seq{vec}
	{
		assert(!seq.empty());
	}

	char GetNext()
	{
		const int prevPos = pos;
		pos = (pos + 1) % static_cast<int>(seq.size());
		return seq[prevPos];
	}
};

template <>
inline std::string Day<8>::PartOne()
{
	partOneDescriptor = "Steps Required to Reach ZZZ (not recalculated)";

	// This part's format changes with the second part.
	return "20659";

	RepeatingSequence seq{parser.GetLine(0)};

	unordered_map<string_view, pair<string_view, string_view>> map;

	for (int i = 2; i < parser.GetNumberOfLines(); ++i)
	{
		const string_view line = parser.GetLine(i);

		vector<string_view> lineParts;
		Parser::Split(line, lineParts, "=", true);

		vector<string_view> pairParts;
		Parser::Split(lineParts[1], pairParts, ",", true);

		// Magic number line split kung-fu
		map[lineParts[0].substr(0, 3)] = {pairParts[0].substr(2), pairParts[1].substr(1, 3)};
	}

	int i = 0;
	for (string_view currPlace = "AAA"; currPlace != "ZZZ"; ++i)
	{
		currPlace = seq.GetNext() == 'L' ? map[currPlace].first : map[currPlace].second;
	}

	return to_string(i);
}

template <>
inline std::string Day<8>::PartTwo()
{
	partTwoDescriptor = "Steps Required to Reach __Z Simultaneously";

	RepeatingSequence seq{parser.GetLine(0)};

	unordered_map<string_view, pair<string_view, string_view>> map;

	vector<string> starts;

	for (int i = 2; i < parser.GetNumberOfLines(); ++i)
	{
		const string_view line = parser.GetLine(i);

		vector<string_view> lineParts;
		Parser::Split(line, lineParts, "=", true);

		vector<string_view> pairParts;
		Parser::Split(lineParts[1], pairParts, ",", true);

		// Magic number line split kung-fu
		map[lineParts[0].substr(0, 3)] = {pairParts[0].substr(2, 3), pairParts[1].substr(1, 3)};

		if (lineParts[0].substr(0, 3).ends_with("A"))
		{
			starts.emplace_back(lineParts[0].substr(0, 3));
		}
	}

	vector<uint64_t> firstZPos;

	for (string currPlace : starts)
	{
		int i = 0;
		for (;!currPlace.ends_with('Z'); ++i)
		{
			currPlace = seq.GetNext() == 'L' ? map[currPlace].first : map[currPlace].second;
		}
		firstZPos.push_back(i);
	}

	return to_string(ranges::fold_left(firstZPos, 1, [](const uint64_t l, const uint64_t r) { return lcm(l, r); }));
}
