#pragma once
#include <string>
#include <string_view>
#include <vector>

class Parser
{
	std::vector<std::string> fileContents;

public:
	explicit Parser(const std::string& parseFilePath);

	[[nodiscard]] std::string_view GetLine(uint32_t lineNumber) const;
	[[nodiscard]] int GetNumberOfLines() const noexcept;

	[[nodiscard]] static int GetNumberFromStringView(std::string_view str);
};

