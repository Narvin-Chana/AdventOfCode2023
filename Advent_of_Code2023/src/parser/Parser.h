#pragma once
#include <set>
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

    template <class ContainerT>
    void Split(const std::string& str, ContainerT& tokens,
        const std::string& delimiters = " ", const bool trimEmpty = false)
    {
        std::string::size_type lastPos = 0;
		const std::string::size_type length = str.length();

		using value_type = typename ContainerT::value_type;
        using size_type = typename ContainerT::size_type;

        while (lastPos < length + 1)
        {
            std::string::size_type pos = str.find_first_of(delimiters, lastPos);
            if (pos == std::string::npos)
                pos = length;

            if (pos != lastPos || !trimEmpty)
                tokens.emplace_back(value_type(str.data() + lastPos,
                    static_cast<size_type>(pos) - lastPos));

            lastPos = pos + 1;
        }
    }

    template <class ContainerT>
    static void Split(std::string_view str, ContainerT& tokens,
        const std::string& delimiters = " ", const bool trimEmpty = false)
    {
        std::string::size_type lastPos = 0;
        const std::string::size_type length = str.length();

        using value_type = typename ContainerT::value_type;
        using size_type = typename ContainerT::size_type;

        while (lastPos < length + 1)
        {
            std::string::size_type pos = str.find_first_of(delimiters, lastPos);
            if (pos == std::string::npos)
                pos = length;

            if (pos != lastPos || !trimEmpty)
            {
                if constexpr (std::is_same_v<ContainerT, std::set<value_type>>)
                {
                    tokens.insert(value_type(str.data() + lastPos, static_cast<size_type>(pos) - lastPos));
                } else
                {
		            tokens.emplace_back(value_type(str.data() + lastPos, static_cast<size_type>(pos) - lastPos));
                }
            }

            lastPos = pos + 1;
        }
    }
};

