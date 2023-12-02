#include <iostream>

#include "days/day1/Day1.h"
#include "days/day2/Day2.h"

int main()
{
	const Day1 day1;
    std::cout << "Day1 - Sum of calibration values: " << day1.FindSumOfCalibrationValues() << '\n';
	const Day2 day2;
    std::cout << "Day2 - Sum of valid game ids: " << day2.CountIDSumOfPossibleGames({12, 13, 14}) << '\n';
    std::cout << "Day2 - Sum of the power of the minimum sets: " << day2.CountIDSumOfPowersOfMinimalSet() << '\n';
}
