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
