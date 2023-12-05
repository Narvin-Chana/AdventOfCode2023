#pragma once

#include <algorithm>
#include <numeric>
#include <ranges>
#include <set>

#include "../Day.h"

struct CardDeck
{
	std::set<std::string_view> winningNumbers;
	std::vector<std::string_view> numbers;

	CardDeck(std::set<std::string_view> winningNumbers, std::vector<std::string_view> numbers)
		: winningNumbers(std::move(winningNumbers)), numbers(std::move(numbers))
	{}

	int GetScorePow()
	{
		auto score = numbers | views::filter([&](auto& num)
		{
			return winningNumbers.contains(num);
		});

		return max(static_cast<const int&>(pow(2, static_cast<int>(std::distance(score.begin(), score.end())) - 1)), 0);
	}

	int GetScore()
	{
		auto score = numbers | views::filter([&](auto& num)
		{
			return winningNumbers.contains(num);
		});

		return static_cast<int>(std::distance(score.begin(), score.end()));
	}

	vector<int> GetScratchCardsWon(int i)
	{
		int score = GetScore();

		if (score == 0)
			return {};

		auto iotaRange = std::views::iota(0, score);

		auto transformedRange = iotaRange | std::views::transform([i](auto val)
		{
			return 1 + val + i;
		});

		return {transformedRange.begin(), transformedRange.end()};
	}
};

inline std::string Day<4>::PartOne()
{
	partOneDescriptor = "Scratch Cards Value";

	int totalScore = 0;

	for (int i = 0; i < parser.GetNumberOfLines(); ++i)
	{
		string_view line = parser.GetLine(i);

		const size_t pos = line.find_first_of(':');
		if (pos == string_view::npos)
		{
			throw std::exception("Bad char");
		}

		const size_t lpos = line.find_last_of('|');
		if (lpos == string_view::npos)
		{
			throw std::exception("Bad char");
		}

		set<string_view> winningNumbers;
		Parser::Split(line.substr(pos + 1, lpos - pos - 1), winningNumbers, " ", true);

		vector<string_view> numbers;
		Parser::Split(line.substr(lpos + 1), numbers, " ", true);

		totalScore += CardDeck(winningNumbers, numbers).GetScorePow();
	}

	return to_string(totalScore);
}

inline std::string Day<4>::PartTwo()
{
	partTwoDescriptor = "Scratch Card Copy Value";

	vector<int> scratchCardTotals;
	scratchCardTotals.resize(parser.GetNumberOfLines());

	for (int i = 0; i < parser.GetNumberOfLines(); ++i)
	{
		++scratchCardTotals[i];
		string_view line = parser.GetLine(i);

		const size_t pos = line.find_first_of(':');
		if (pos == string_view::npos)
		{
			throw std::exception("Bad char");
		}

		const size_t lpos = line.find_last_of('|');
		if (lpos == string_view::npos)
		{
			throw std::exception("Bad char");
		}

		set<string_view> winningNumbers;
		Parser::Split(line.substr(pos + 1, lpos - pos - 1), winningNumbers, " ", true);

		vector<string_view> numbers;
		Parser::Split(line.substr(lpos + 1), numbers, " ", true);

		for (vector<int> scratchCardsWon = CardDeck(winningNumbers, numbers).GetScratchCardsWon(i); const int val : scratchCardsWon)
		{
			scratchCardTotals[val] += scratchCardTotals[i];
		}
	}

	return to_string(std::accumulate(scratchCardTotals.begin(), scratchCardTotals.end(), 0));
}
