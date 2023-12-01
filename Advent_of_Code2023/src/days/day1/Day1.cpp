#include "Day1.h"

#include <ranges>

using namespace std;

Day1::Day1() : parser(InputFile)
{
}

int Day1::FindSumOfCalibrationValues() const
{
	int totalSum = 0;

	for (int lineNb = 0; lineNb < parser.GetNumberOfLines(); ++lineNb)
	{
		int firstNumberPos = numeric_limits<int>::max();
		int lastNumberPos = numeric_limits<int>::min();

		char firstNum = 'N';
		char lastNum = 'N';

		auto line = parser.GetLine(lineNb);

		for (size_t i = 0; i < digits.size(); ++i)
		{
			if (const size_t foundPos = line.find(digits[i]); foundPos != std::string_view::npos)
			{
				if (static_cast<int>(foundPos) < firstNumberPos)
				{
					firstNumberPos = static_cast<int>(foundPos);
					firstNum = static_cast<char>('1' + static_cast<char>(i));
				}
			}

			if (const size_t foundPos = line.rfind(digits[i]); foundPos != string_view::npos)
			{
				if (static_cast<int>(foundPos) > lastNumberPos)
				{
					lastNumberPos = static_cast<int>(foundPos);
					lastNum = static_cast<char>('1' + static_cast<char>(i));
				}
			}
		}

		for (int i = 0; i < static_cast<int>(line.size()); ++i)
		{
			if (isdigit(line[i]))
			{
				if (i < firstNumberPos)
				{
					firstNumberPos = i;
					firstNum = line[i];
				}

				if (i > lastNumberPos)
				{
					lastNumberPos = i;
					lastNum = line[i];
				}
			}
		}

		totalSum += stoi(string{firstNum} + string{lastNum});
	}

	return totalSum;
}
