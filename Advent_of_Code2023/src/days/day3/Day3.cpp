#include "Day3.h"

#include <algorithm>
#include <charconv>

using namespace std;

Day3::Day3() :
	parser(InputFile)
{}


int Day3::GetSumOfPartNumbers() const
{
	int sumOfParts = 0;

	string_view previousLine;

	for (int i = 0; i < parser.GetNumberOfLines(); ++i)
	{
		string_view line = parser.GetLine(i);

		int currentIndex = 0;
		while (currentIndex < static_cast<int>(line.size()))
		{
			string_view currLine = line.substr(currentIndex);

			const size_t nonSepChar = currLine.find_first_of("0123456789");
			if (nonSepChar == string_view::npos)
				break;

			size_t nextSepChar = currLine.substr(nonSepChar).find_first_not_of("0123456789");

			if (nextSepChar == string_view::npos)
				nextSepChar = currLine.size() - 1;

			// Get number
			string_view number = currLine.substr(nonSepChar, nextSepChar);
			const int partNumber = Parser::GetNumberFromStringView(number);

			// Determine if the number is valid

			// Check before and after the number in the same line
			const int indexBefore = max(currentIndex + static_cast<int>(nonSepChar) - 1, 0);
			const int indexAfter = min(currentIndex + static_cast<int>(nonSepChar + number.size()), static_cast<int>(line.size()) - 1);

			if (line.substr(indexBefore, 1).find_first_of(".\n0123456789") == string_view::npos or line.substr(indexAfter, 1).find_first_of(".\n0123456789") == string_view::npos)
			{
				sumOfParts += partNumber;
				currentIndex += static_cast<int>(nextSepChar + nonSepChar);
				continue;
			}

			// Check previous line
			if (!previousLine.empty())
			{
				if (DoesLineSubstringContainSymbol(previousLine, max(currentIndex + static_cast<int>(nonSepChar) - 1, 0), min(currentIndex + static_cast<int>(nonSepChar + number.size()), static_cast<int>(previousLine.size()) - 1)))
				{
					sumOfParts += partNumber;
					currentIndex += static_cast<int>(nextSepChar + nonSepChar);
					continue;
				}
			}

			// Check next line
			if (i < parser.GetNumberOfLines() - 1)
			{
				if (string_view nextLine = parser.GetLine(i + 1); DoesLineSubstringContainSymbol(nextLine, max(currentIndex + static_cast<int>(nonSepChar) - 1, 0), min(currentIndex + static_cast<int>(nonSepChar + number.size()), static_cast<int>(nextLine.size()) - 1)))
				{
					sumOfParts += partNumber;
					currentIndex += static_cast<int>(nextSepChar + nonSepChar);
					continue;
				}
			}

			currentIndex += static_cast<int>(nextSepChar + nonSepChar);
		}
		previousLine = line;
	}

	return sumOfParts;
}

int Day3::GetSumOfGearRatios() const
{
	int sumOfGearRatios = 0;

	string_view previousLine;

	for (int i = 0; i < parser.GetNumberOfLines(); ++i)
	{
		string_view line = parser.GetLine(i);

		int currentIndex = 0;
		while (currentIndex < static_cast<int>(line.size()))
		{
			string_view currLine = line.substr(currentIndex);

			const size_t gearIndex = currLine.find('*');
			if (gearIndex == string_view::npos)
				break;

			int numberOfNeighbouringPartNumbers = 0;
			int gearRatio = 0;

			// Check all directions in this interval
			const int leftMostIndex = max(currentIndex + static_cast<int>(gearIndex) - 1, 0);
			const int rightMostIndex = min(currentIndex + static_cast<int>(gearIndex) + 1, static_cast<const int&>(line.size()));

			// Before and after the *
			if (currentIndex + static_cast<int>(gearIndex) > 0 && isdigit(line[leftMostIndex]))
			{
				string_view leftSide = line.substr(0, leftMostIndex + 1);
				if (const size_t lastPosBeforeNumber = leftSide.find_last_not_of("0123456789"); lastPosBeforeNumber != string_view::npos || !leftSide.contains('*'))
				{
					const int partNumber = Parser::GetNumberFromStringView(leftSide.substr(lastPosBeforeNumber + 1));
					gearRatio = gearRatio == 0 ? partNumber : gearRatio * partNumber;
					++numberOfNeighbouringPartNumbers;
				}
			}
			if (currentIndex + static_cast<int>(gearIndex) < static_cast<int>(line.size()) && isdigit(line[rightMostIndex]))
			{
				string_view rightSide = line.substr(rightMostIndex);
				if (const size_t lastPosBeforeNumber = rightSide.find_first_not_of("0123456789"); lastPosBeforeNumber != string_view::npos || !rightSide.contains('*'))
				{
					const int partNumber = Parser::GetNumberFromStringView(rightSide.substr(0, lastPosBeforeNumber - rightMostIndex));
					gearRatio = gearRatio == 0 ? partNumber : gearRatio * partNumber;
					++numberOfNeighbouringPartNumbers;
				}
			}

			size_t index = 0;
			// Previous line check
			{
				string_view prev = previousLine;
				while(!prev.empty())
				{
					const size_t numberStartIndex = prev.find_first_of("0123456789");
					if (numberStartIndex == string_view::npos)
						break;

					size_t numberEndIndex = prev.substr(numberStartIndex).find_first_not_of("0123456789");

					if (numberEndIndex == string_view::npos)
						numberEndIndex = prev.size() - numberStartIndex - 1;

					if (numberStartIndex + numberEndIndex + index <= leftMostIndex)
					{
						index += numberStartIndex + numberEndIndex;
						prev = prev.substr(numberStartIndex + numberEndIndex);
						continue;
					}

					if (numberStartIndex + index > rightMostIndex)
					{
						break;
					}

					const string_view num = prev.substr(numberStartIndex, numberEndIndex);
					const int partNumber = Parser::GetNumberFromStringView(num);

					gearRatio = gearRatio == 0 ? partNumber : gearRatio * partNumber;
					++numberOfNeighbouringPartNumbers;
					index += numberStartIndex + numberEndIndex;
					prev = prev.substr(numberStartIndex + numberEndIndex);
				}
			}

			// Next line check
			if (i < parser.GetNumberOfLines() - 1)
			{
				index = 0;
				string_view next = parser.GetLine(i + 1);
				while (!next.empty())
				{
					const size_t numberStartIndex = next.find_first_of("0123456789");
					if (numberStartIndex == string_view::npos)
						break;

					size_t numberEndIndex = next.substr(numberStartIndex).find_first_not_of("0123456789");
					if (numberEndIndex == string_view::npos)
						numberEndIndex = next.size() - numberStartIndex - 1;

					if (numberStartIndex + numberEndIndex + index <= leftMostIndex)
					{
						index += numberStartIndex + numberEndIndex;
						next = next.substr(numberStartIndex + numberEndIndex);
						continue;
					}

					if (numberStartIndex + index > rightMostIndex)
					{
						break;
					}

					const string_view num = next.substr(numberStartIndex, numberEndIndex);
					const int partNumber = Parser::GetNumberFromStringView(num);

					gearRatio = gearRatio == 0 ? partNumber : gearRatio * partNumber;
					++numberOfNeighbouringPartNumbers;
					index += numberStartIndex + numberEndIndex;
					next = next.substr(numberStartIndex + numberEndIndex);
				}
			}

			// Only increment if == 2
			if (numberOfNeighbouringPartNumbers == 2)
			{
				sumOfGearRatios += gearRatio;
			}

			currentIndex += static_cast<int>(gearIndex + 1);
		}
		previousLine = line;
	}

	return sumOfGearRatios;
}

bool Day3::DoesLineSubstringContainSymbol(const std::string_view line, const size_t firstPos, const size_t lastPos)
{
	const size_t pos = line.substr(firstPos, lastPos - firstPos + 1).find_first_not_of(".\n0123456789");
	return pos != string_view::npos;
}
