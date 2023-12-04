#include "Parser.h"

#include <cassert>
#include <fstream>

using namespace std;

Parser::Parser(const string& parseFilePath)
{
	ifstream ifs(parseFilePath);
	string content;

	while(getline(ifs, content))
	{
		fileContents.push_back(content);
	}
}

string_view Parser::GetLine(const uint32_t lineNumber) const
{
	assert(lineNumber < fileContents.size() && !fileContents.empty());
	return fileContents[lineNumber];
}

int Parser::GetNumberOfLines() const noexcept
{
	return static_cast<int>(fileContents.size());
}

int Parser::GetNumberFromStringView(const std::string_view str)
{
	int num;
	if (const auto [ptr, ec] = from_chars(str.data(), str.data() + str.size(), num); ec == errc::invalid_argument)
	{
		throw exception("Invalid number was parsed...");
	}
	return num;
}
