#pragma once
#include <tuple>

#include "Day.h"

// GenerateDaySequence to generate Day types from 1 to N
template <std::size_t N, typename Indices = std::make_index_sequence<N>>
struct GenerateDaySequence;

template <std::size_t N, std::size_t... Indices>
struct GenerateDaySequence<N, std::index_sequence<Indices...>>
{
	using type = std::tuple<Day<Indices + 1>...>;
};
