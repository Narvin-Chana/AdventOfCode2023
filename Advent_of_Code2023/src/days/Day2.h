#pragma once
#include <charconv>
#include <string>
#include "../Day.h"

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

inline std::string Day<2>::PartOne()
{
	constexpr Bag bag{12, 13, 14};
	partOneDescriptor = "Sum of valid game ids";

	int sumOfIds = 0;

	for (int i = 0; i < parser.GetNumberOfLines(); ++i)
	{
		std::string_view line = parser.GetLine(i);

		static constexpr int IDStartIndex = 5;
		const int idEndIndex = static_cast<int>(line.find(':'));

		string_view id = line.substr(IDStartIndex, idEndIndex);

		int currGameId = 0;
		if (std::from_chars(id.data(), id.data() + id.size(), currGameId).ec == errc::invalid_argument)
		{
			throw exception("WhoopsID...");
		}

		line = line.substr(idEndIndex);

		bool isPossible = true;

		while (!line.empty())
		{
			const size_t endOfSet = line.find_first_of(';');

			string_view set = line.substr(0, endOfSet);

			if (const size_t pos = set.find("red"); pos != string_view::npos)
			{
				int redCubesVal = 0;
				string_view subStr = set.substr(pos - 3, 4);
				// Remove whitespace
				subStr = subStr.substr(subStr.find_first_not_of(" \t\n\r\f\v"), subStr.find_last_not_of(" \t\n\r\f\v"));

				if (std::from_chars(subStr.data(), subStr.data() + subStr.size(), redCubesVal).ec == errc::invalid_argument)
				{
					throw exception("WhoopsR...");
				}
				if (redCubesVal > bag.redCubes)
				{
					isPossible = false;
					break;
				}
			}
			if (const size_t pos = set.find("green"); pos != string_view::npos)
			{
				int greenCubesVal = 0;
				string_view subStr = set.substr(pos - 3, 4);
				// Remove whitespace
				subStr = subStr.substr(subStr.find_first_not_of(" \t\n\r\f\v"), subStr.find_last_not_of(" \t\n\r\f\v"));

				if (std::from_chars(subStr.data(), subStr.data() + subStr.size(), greenCubesVal).ec == errc::invalid_argument)
				{
					throw exception("WhoopsG...");
				}
				if (greenCubesVal > bag.greenCubes)
				{
					isPossible = false;
					break;
				}
			}
			if (const size_t pos = set.find("blue"); pos != string_view::npos)
			{
				int blueCubes = 0;
				string_view subStr = set.substr(pos - 3, 4);
				// Remove whitespace
				subStr = subStr.substr(subStr.find_first_not_of(" \t\n\r\f\v"), subStr.find_last_not_of(" \t\n\r\f\v"));

				if (std::from_chars(subStr.data(), subStr.data() + subStr.size(), blueCubes).ec == errc::invalid_argument)
				{
					throw exception("WhoopsB...");
				}
				if (blueCubes > bag.blueCubes)
				{
					isPossible = false;
					break;
				}
			}

			if (endOfSet == string_view::npos)
				break;

			line = line.substr(endOfSet + 1);
		}

		if (isPossible)
		{
			sumOfIds += currGameId;
		}
	}

	return to_string(sumOfIds);
}

inline std::string Day<2>::PartTwo()
{
	partTwoDescriptor = "Sum of the power of the minimum sets";

	int sumOfPowers = 0;

	for (int i = 0; i < parser.GetNumberOfLines(); ++i)
	{
		std::string_view line = parser.GetLine(i);
		const int idEndIndex = static_cast<int>(line.find(':'));
		line = line.substr(idEndIndex);

		Bag bag{numeric_limits<int>::min(), numeric_limits<int>::min(), numeric_limits<int>::min()};

		while (!line.empty())
		{
			const size_t endOfSet = line.find_first_of(';');

			string_view set = line.substr(0, endOfSet);

			if (const size_t pos = set.find("red"); pos != string_view::npos)
			{
				int redCubesVal = 0;
				string_view subStr = set.substr(pos - 3, 4);
				// Remove whitespace
				subStr = subStr.substr(subStr.find_first_not_of(" \t\n\r\f\v"), subStr.find_last_not_of(" \t\n\r\f\v"));

				if (std::from_chars(subStr.data(), subStr.data() + subStr.size(), redCubesVal).ec == errc::invalid_argument)
				{
					throw exception("WhoopsR...");
				}
				if (redCubesVal > bag.redCubes)
				{
					bag.redCubes = redCubesVal;
				}
			}
			if (const size_t pos = set.find("green"); pos != string_view::npos)
			{
				int greenCubesVal = 0;
				string_view subStr = set.substr(pos - 3, 4);
				// Remove whitespace
				subStr = subStr.substr(subStr.find_first_not_of(" \t\n\r\f\v"), subStr.find_last_not_of(" \t\n\r\f\v"));

				if (std::from_chars(subStr.data(), subStr.data() + subStr.size(), greenCubesVal).ec == errc::invalid_argument)
				{
					throw exception("WhoopsG...");
				}
				if (greenCubesVal > bag.greenCubes)
				{
					bag.greenCubes = greenCubesVal;
				}
			}
			if (const size_t pos = set.find("blue"); pos != string_view::npos)
			{
				int blueCubes = 0;
				string_view subStr = set.substr(pos - 3, 4);
				// Remove whitespace
				subStr = subStr.substr(subStr.find_first_not_of(" \t\n\r\f\v"), subStr.find_last_not_of(" \t\n\r\f\v"));

				if (std::from_chars(subStr.data(), subStr.data() + subStr.size(), blueCubes).ec == errc::invalid_argument)
				{
					throw exception("WhoopsB...");
				}
				if (blueCubes > bag.blueCubes)
				{
					bag.blueCubes = blueCubes;
				}
			}

			if (endOfSet == string_view::npos)
				break;

			line = line.substr(endOfSet + 1);
		}

		sumOfPowers += bag.GetPower();
	}

	return to_string(sumOfPowers);
}
