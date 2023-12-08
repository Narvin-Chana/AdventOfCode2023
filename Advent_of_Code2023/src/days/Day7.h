#pragma once

#include <unordered_map>

#include "../Day.h"

enum Card : char
{
	ACE = 'A',
	KING = 'K',
	QUEEN = 'Q',
	JESTER = 'J',
	TEN = 'T',
	NINE = '9',
	EIGHT = '8',
	SEVEN = '7',
	SIX = '6',
	FIVE = '5',
	FOUR = '4',
	THREE = '3',
	TWO = '2'
};

struct CardHand
{
	inline static map<Card, int> CardRanking{
		{ACE, 0},
		{KING, 1},
		{QUEEN, 2},
		{JESTER, 3},
		{TEN, 4},
		{NINE, 5},
		{EIGHT, 6},
		{SEVEN, 7},
		{SIX, 8},
		{FIVE, 9},
		{FOUR, 10},
		{THREE, 11},
		{TWO, 12}
	};

	inline static map<Card, int> CardRankingJoker{
		{ACE, 0},
		{KING, 1},
		{QUEEN, 2},
		{TEN, 3},
		{NINE, 4},
		{EIGHT, 5},
		{SEVEN, 6},
		{SIX, 7},
		{FIVE, 8},
		{FOUR, 9},
		{THREE, 10},
		{TWO, 11},
		{JESTER, 12}
	};

	static constexpr int CardHandSize = 5;

	array<Card, CardHandSize> hand;
	array<Card, CardHandSize> jokerHand;

	enum CardHandType : short
	{
		FIVE_OF_A_KIND = 0,
		FOUR_OF_A_KIND,
		FULL_HOUSE,
		THREE_OF_A_KIND,
		TWO_PAIR,
		ONE_PAIR,
		HIGH_CARD
	} type;

	int bid = 0;

	CardHand(const string_view line, const int bid, const bool hasSpecialJoker = false)
		: bid(bid)
	{
		for (int i = 0; i < static_cast<int>(line.size()); ++i)
		{
			hand[i] = static_cast<Card>(line[i]);
		}
		if (!hasSpecialJoker)
			GetTypeFromHand();
		else
			GetTypeFromHandJoker();
	}

	void GetTypeFromHand()
	{
		unordered_map<Card, int> cardCountMap;

		for (auto card : hand)
		{
			if (!cardCountMap.contains(card))
			{
				cardCountMap[card] = 1;
			}
			else
			{
				++cardCountMap[card];
			}
		}

		if (cardCountMap.size() == 1)
		{
			type = FIVE_OF_A_KIND;
			return;
		}

		if (MapContainsValue(4, cardCountMap))
		{
			type = FOUR_OF_A_KIND;
			return;
		}

		const bool containsTruple = MapContainsValue(3, cardCountMap);
		const bool containsPair = MapContainsValue(2, cardCountMap);

		if (containsTruple && containsPair)
		{
			type = FULL_HOUSE;
		}
		else if (containsTruple)
		{
			type = THREE_OF_A_KIND;
		}
		else if (containsPair && MapContainsValueTwice(2, cardCountMap))
		{
			type = TWO_PAIR;
		}
		else if (containsPair)
		{
			type = ONE_PAIR;
		}
		else if (cardCountMap.size() == CardHandSize)
		{
			type = HIGH_CARD;
		}
	}

	void GetTypeFromHandJoker()
	{
		unordered_map<Card, int> cardCountMap;

		// Keep track of hand with jokers for if we need to compare (element-wise) two type-matching hands
		jokerHand = hand;

		for (auto card : hand)
		{
			if (!cardCountMap.contains(card))
			{
				cardCountMap[card] = 1;
			}
			else
			{
				++cardCountMap[card];
			}
		}

		// Replace joker with highest card apparition
		if (cardCountMap.contains(JESTER))
		{
			cardCountMap[JESTER] = 0;
			const auto maxValIt = ranges::max_element(cardCountMap,
													  [](const pair<Card, int>& left, const pair<Card, int>& right)
													  {
														  if (left.second == right.second)
														  {
															  return CardRankingJoker[left.first] < CardRankingJoker[right.first];
														  }

														  return left.second < right.second;
													  });

			assert(maxValIt != cardCountMap.end());

			const Card maxValueCard = maxValIt->first;

			for (Card& card : hand)
			{
				if (card == JESTER)
				{
					card = maxValueCard;
				}
			}
		}

		GetTypeFromHand();
	}

	bool Compare(const CardHand& other) const
	{
		if (type != other.type)
			return type >= other.type;

		for (int i = 0; i < CardHandSize; ++i)
		{
			if (hand[i] == other.hand[i])
				continue;
			return CardRanking[hand[i]] >= CardRanking[other.hand[i]];
		}

		return false;
	}

	bool CompareJoker(const CardHand& other) const
	{
		if (type != other.type)
			return type >= other.type;

		for (int i = 0; i < CardHandSize; ++i)
		{
			if (jokerHand[i] == other.jokerHand[i])
				continue;
			return CardRankingJoker[jokerHand[i]] >= CardRankingJoker[other.jokerHand[i]];
		}

		return false;
	}

private:
	bool MapContainsValue(int value, auto& cardCountMap)
	{
		const auto it = ranges::find_if(cardCountMap,
										[&](auto& key)
										{
											return key.second == value;
										});
		return it != cardCountMap.end();
	}

	bool MapContainsValueTwice(int value, auto& cardCountMap)
	{
		const auto it = ranges::find_if(cardCountMap,
										[&](auto& key)
										{
											return key.second == value;
										});

		if (it == cardCountMap.end())
			return false;

		const auto secondTimeIt = ranges::find_if(cardCountMap,
												  [&](auto& key)
												  {
													  return static_cast<char>(key.first) != static_cast<char>(it->first) && key.second == value;
												  });

		return secondTimeIt != cardCountMap.end();
	}
};

//template <>
//struct Day<7>::IsImplemented
//{
//	static constexpr bool value = true;
//};

template <>
inline std::string Day<7>::PartOne()
{
	partOneDescriptor = "Sum of the Bids of each Card Hand Times Their Rank";

	vector<CardHand> cardHands;

	for (int i = 0; i < parser.GetNumberOfLines(); ++i)
	{
		const string_view line = parser.GetLine(i);

		vector<string_view> handBid;
		Parser::Split(line, handBid, " ", true);

		assert(handBid.size() == 2);

		cardHands.emplace_back(handBid[0], Parser::GetNumberFromStringView<int>(handBid[1]));
	}
	// Sort cardHands
	ranges::sort(cardHands,
				 [](const CardHand& left, const CardHand& right)
				 {
					 return left.Compare(right);
				 });

	int sumOfTheBidsOfEachCardHand = 0;

	for (int i = 0; i < static_cast<int>(cardHands.size()); ++i)
	{
		sumOfTheBidsOfEachCardHand += (i + 1) * cardHands[i].bid;
	}

	return to_string(sumOfTheBidsOfEachCardHand);
}

template <>
inline std::string Day<7>::PartTwo()
{
	partTwoDescriptor = "Sum of the Bids of each Card Hand Times Their Rank With Joker";

	vector<CardHand> cardHands;

	for (int i = 0; i < parser.GetNumberOfLines(); ++i)
	{
		const string_view line = parser.GetLine(i);

		vector<string_view> handBid;
		Parser::Split(line, handBid, " ", true);

		assert(handBid.size() == 2);

		cardHands.emplace_back(handBid[0], Parser::GetNumberFromStringView<int>(handBid[1]), true);
	}
	// Sort cardHands
	ranges::sort(cardHands,
				 [](const CardHand& left, const CardHand& right)
				 {
					 return left.CompareJoker(right);
				 });

	int sumOfTheBidsOfEachCardHand = 0;

	for (int i = 0; i < static_cast<int>(cardHands.size()); ++i)
	{
		sumOfTheBidsOfEachCardHand += (i + 1) * cardHands[i].bid;
	}

	return to_string(sumOfTheBidsOfEachCardHand);
}
