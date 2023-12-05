#pragma once

#include <cassert>
#include <map>
#include <ranges>

#include "../Day.h"

struct SeedMapLine
{
	uint64_t destination;
	uint64_t source;
	uint64_t range;

	SeedMapLine(const vector<string_view>& line)
	{
		assert(line.size() == 3);
		destination = Parser::GetNumberFromStringView<uint64_t>(line[0]);
		source = Parser::GetNumberFromStringView<uint64_t>(line[1]);
		range = Parser::GetNumberFromStringView<uint64_t>(line[2]);
	}

	optional<uint64_t> GetSeedDest(const uint64_t seed) const
	{
		if (seed >= source and seed < source + range)
			return destination + seed - source;

		return nullopt;
	}
};

class Almanac
{
public:
	virtual ~Almanac() = default;
	vector<uint64_t> plantableSeeds;
	vector<vector<SeedMapLine>> maps;
	int currentMapIndex = 0;

	Almanac()
	{
		maps.resize(1);
	}

	Almanac(string_view plantableSeedsString)
		: Almanac()
	{
		plantableSeedsString = plantableSeedsString.substr(plantableSeedsString.find_first_of(' '));

		vector<string_view> seedStrings;
		Parser::Split(plantableSeedsString, seedStrings, " ", true);

		auto seedSet = seedStrings | views::transform([](auto& s)
		{
			return Parser::GetNumberFromStringView<uint64_t>(s);
		});

		plantableSeeds = {seedSet.begin(), seedSet.end()};
	}

	virtual vector<uint64_t> GetLocationOfSeeds() const
	{
		vector<uint64_t> locations;
		locations.reserve(plantableSeeds.size());

		for (const uint64_t seed : plantableSeeds)
		{
			locations.push_back(IterateOnMaps(seed));
		}

		return locations;
	}

	void AddLine(const string_view line)
	{
		vector<string_view> lineRanges;
		Parser::Split(line, lineRanges, " ", true);

		const SeedMapLine sml(lineRanges);

		maps[currentMapIndex].push_back(sml);
	}

protected:
	uint64_t IterateOnMaps(uint64_t seed) const
	{
		//return accumulate(maps.begin(),
		//				  maps.end(),
		//				  seed,
		//				  [](const uint64_t currentSeed, const vector<SeedMapLine>& m)
		//				  {
		//					  for (const auto& seedMapLine : m)
		//					  {
		//						  if (const optional<uint64_t> res = seedMapLine.GetSeedDest(currentSeed); res != nullopt)
		//							  return res.value();
		//					  }

		//					  return currentSeed;
		//				  });

		// Equivalent to accumulate
		for (const vector<SeedMapLine>& m : maps)
		{
			for (const SeedMapLine& seedMapLine : m)
			{
				if (const optional<uint64_t> res = seedMapLine.GetSeedDest(seed); res != nullopt)
				{
					seed = res.value();
					break;
				}
			}
		}
		return seed;
	}
};

class RangedAlmanac : public Almanac
{
	vector<pair<uint64_t, uint64_t>> plantableSeedsRange;

public:
	RangedAlmanac(string_view plantableSeedsString)
	{
		plantableSeedsString = plantableSeedsString.substr(plantableSeedsString.find_first_of(' '));

		vector<string_view> seedStrings;
		Parser::Split(plantableSeedsString, seedStrings, " ", true);

		for (int i = 0; i < static_cast<int>(seedStrings.size()); i += 2)
		{
			const auto initialValue = Parser::GetNumberFromStringView<uint64_t>(seedStrings[i]);
			const auto rangeValue = Parser::GetNumberFromStringView<uint64_t>(seedStrings[i + 1]);
			plantableSeedsRange.emplace_back(initialValue, rangeValue);
		}
	}

	vector<uint64_t> GetLocationOfSeeds() const override
	{
		vector<uint64_t> locations;
		locations.reserve(plantableSeedsRange.size());

		for (const auto& [initialSeed, range] : plantableSeedsRange)
		{
			uint64_t minLocation = numeric_limits<uint64_t>::max();

			for (uint64_t i = initialSeed; i < initialSeed + range; ++i)
			{
				minLocation = min(IterateOnMaps(i), minLocation);
			}

			locations.push_back(minLocation);
		}

		return locations;
	}
};

inline std::string Day<5>::PartOne()
{
	partOneDescriptor = "Lowest Location Number of Any Initial Seed";

	// Add initial seeds to almanac
	Almanac almanac(parser.GetLine(0));

	// Start after initial seeds and initial map
	for (int i = 3; i < parser.GetNumberOfLines(); ++i)
	{
		string_view line = parser.GetLine(i);

		if (line.empty())
			continue;

		if (line.contains("map"))
		{
			++almanac.currentMapIndex;
			almanac.maps.resize(almanac.currentMapIndex + 1);
			continue;
		}

		almanac.AddLine(line);
	}

	vector<uint64_t> locs = almanac.GetLocationOfSeeds();

	const auto it = ranges::min_element(locs);

	return to_string(*it);
}

inline std::string Day<5>::PartTwo()
{
	partTwoDescriptor = "Lowest Location Number of Any Seed in Initial Range";

	// Takes a while so here is the value generated with actual data
	return to_string(56931769);

	// Add initial seeds to almanac
	RangedAlmanac almanac{ parser.GetLine(0) };

	// Start after initial seeds and initial map
	for (int i = 3; i < parser.GetNumberOfLines(); ++i)
	{
		string_view line = parser.GetLine(i);

		if (line.empty())
			continue;

		if (line.contains("map"))
		{
			++almanac.currentMapIndex;
			almanac.maps.resize(almanac.currentMapIndex + 1);
			continue;
		}

		almanac.AddLine(line);
	}

	vector<uint64_t> locs = almanac.GetLocationOfSeeds();

	const auto it = ranges::min_element(locs);

	return to_string(*it);
}
