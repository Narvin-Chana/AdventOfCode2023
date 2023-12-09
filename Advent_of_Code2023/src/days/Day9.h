#pragma once

#include "../Day.h"

struct Sequence
{
	vector<vector<int>> histories;

	Sequence(const vector<int>& history)
	{
		histories.push_back(history);

		// Generate differences vectors
		do
		{
			vector<int> diffs;

			optional<int> prevVal = nullopt;
			for (const int val : histories.back())
			{
				if (!prevVal)
				{
					prevVal = val;
					continue;
				}

				diffs.push_back(val - *prevVal);
				prevVal = val;
			}

			histories.push_back(diffs);
		}
		while (!ranges::all_of(histories.back(),
							  [](const int i)
							  {
								  return i == 0;
							  }));
	}

	int GetNextVal()
	{
		for (int i = static_cast<int>(histories.size()) - 1; i >= 1; --i)
		{
			histories[i - 1].push_back(histories[i - 1].back() + histories[i].back());
		}
		return histories.front().back();
	}

	int GetPrevVal()
	{
		// Add bonus 0 to start of 0 vector (or add to back since its just a vec of zeroes)
		histories.back().push_back(0);

		// Get value of past extrapolation
		for (int i = static_cast<int>(histories.size()) - 1; i >= 1; --i)
		{
			histories[i - 1].insert(begin(histories[i - 1]), histories[i - 1].front() - histories[i].front());
		}
		return histories.front().front();
	}
};

template <>
inline std::string Day<9>::PartOne()
{
	partOneDescriptor = "Sum of Next Extrapolated Values";

	int sum = 0;

	for (int i = 0; i < parser.GetNumberOfLines(); ++i)
	{
		vector<string_view> history;
		Parser::Split(parser.GetLine(i), history, " ", true);

		vector<int> historyInt;
		ranges::transform(history, back_inserter(historyInt), Parser::GetNumberFromStringView<int>);

		sum += Sequence{ historyInt }.GetNextVal();
	}

	return to_string(sum);
}

template <>
inline std::string Day<9>::PartTwo()
{
	partTwoDescriptor = "Sum of Previous Extrapolated Values";

	int sum = 0;

	for (int i = 0; i < parser.GetNumberOfLines(); ++i)
	{
		vector<string_view> history;
		Parser::Split(parser.GetLine(i), history, " ", true);

		vector<int> historyInt;
		ranges::transform(history, back_inserter(historyInt), Parser::GetNumberFromStringView<int>);

		sum += Sequence{ historyInt }.GetPrevVal();
	}

	return to_string(sum);
}
