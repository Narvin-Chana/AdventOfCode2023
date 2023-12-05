#pragma once
#include <array>
#include <string>
#include "../Day.h"

inline static const std::array<std::string, 9> Digits = {
	"one", "two", "three", "four",
	"five", "six", "seven", "eight",
	"nine"
};

inline std::string Day<1>::PartOne()
{
	partOneDescriptor = "Sum of calibration values";

	int totalSum = 0;

	for (int lineNb = 0; lineNb < parser.GetNumberOfLines(); ++lineNb)
	{
		int firstNumberPos = std::numeric_limits<int>::max();
		int lastNumberPos = std::numeric_limits<int>::min();

		char firstNum = 'N';
		char lastNum = 'N';

		auto line = parser.GetLine(lineNb);

		for (size_t i = 0; i < Digits.size(); ++i)
		{
			if (const size_t foundPos = line.find(Digits[i]); foundPos != std::string_view::npos)
			{
				if (static_cast<int>(foundPos) < firstNumberPos)
				{
					firstNumberPos = static_cast<int>(foundPos);
					firstNum = static_cast<char>('1' + static_cast<char>(i));
				}
			}

			if (const size_t foundPos = line.rfind(Digits[i]); foundPos != std::string_view::npos)
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

		totalSum += std::stoi(std::string{firstNum} + std::string{lastNum});
	}

	return std::to_string(totalSum);
}

template <>
inline std::string Day<1>::PartTwo()
{
	partTwoDescriptor = "Sum of calibration values";

	return PartOne();
}
