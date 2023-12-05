#include "DayExecutor.h"

#include "days/Day1.h"
#include "days/Day2.h"
#include "days/Day3.h"
#include "days/Day4.h"

int main()
{
	static constexpr size_t DayCount = 4;

	using AllDays = GenerateDaySequence<DayCount>::type;
	auto days = AllDays{};
	apply([](auto&&... day) { (day.ExecuteParts(), ...); }, days);
}
