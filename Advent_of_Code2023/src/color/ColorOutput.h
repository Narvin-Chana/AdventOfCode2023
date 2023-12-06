#pragma once
#include <ostream>
#include <string>

struct ColorTable
{
	enum Color
	{
		BLACK = 30,
		RED = 31,
		GREEN = 32,
		YELLOW = 33,
		BLUE = 34,
		MAGENTA = 35,
		CYAN = 36,
		WHITE = 37,
		BRIGHTBLACK = 90,
		BRIGHTRED = 91,
		BRIGHTGREEN = 92,
		BRIGHTYELLOW = 93,
		BRIGHTBLUE = 94,
		BRIGHTMAGENTA = 95,
		BRIGHTCYAN = 96,
		BRIGHTWHITE = 97
	};
};

struct ColorOutput
{
	std::string str;

	ColorTable::Color color = ColorTable::WHITE;

	ColorOutput(const std::string_view str, const ColorTable::Color c)
		: str{str}, color{c} {}

	friend std::ostream& operator<<(std::ostream& os, const ColorOutput& co)
	{
		return os << std::string("\x1B[") + std::format("{}m", std::to_string(co.color)) + co.str + std::string("\033[0m");
	}
};
