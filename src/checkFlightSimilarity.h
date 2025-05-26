#pragma once

#include <string>
#include <exception>

// Version 1 slower coz exception

bool checkFlightSimilarty(const std::string& c_first, const std::string& c_second)
{
	if (c_first.size() > 7 || c_second.size() > 7) {
		throw std::length_error(std::string("at function [").append(__func__).append("] ")
			.append("at least one of the flights is longer than max of 7 symbols ")
			.append("First = ").append(std::to_string(c_first.size()))
			.append(" Second = ").append(std::to_string(c_second.size()))
		);
	}

	auto first_it = c_first.rbegin();
	auto second_it = c_second.rbegin();

	auto firstEnd = c_first.rend();
	auto secondEnd = c_second.rend();

	auto skipNonSignificant = [](auto& it, auto& end) {
		while (it != end && (*it == '0' || *it == ' '))
			++it;
		};

	while (first_it != firstEnd || second_it != secondEnd) {
		if (*first_it != *second_it) {
			return false;
		}

		first_it++;
		second_it++;

		skipNonSignificant(first_it, firstEnd);
		skipNonSignificant(second_it, secondEnd);
	}

	return (first_it == firstEnd) && (second_it == secondEnd);
}

// Version 2 faster nonexcept

bool checkFlightSimilarty(const std::string& c_first, const std::string& c_second, std::string& error) noexcept
{
	if (c_first.size() > 7 || c_second.size() > 7) {
		error.append("At function [").append(__func__).append("] ")
			.append("at least one of the flights is longer than max of 7 symbols ")
			.append("First = ").append(std::to_string(c_first.size()))
			.append(" Second = ").append(std::to_string(c_second.size()));
	}

	auto first_it = c_first.rbegin();
	auto second_it = c_second.rbegin();

	auto firstEnd = c_first.rend();
	auto secondEnd = c_second.rend();

	auto skipNonSignificant = [](auto& it, auto& end) {
		while (it != end && (*it == '0' || *it == ' '))
			++it;
		};

	while (first_it != firstEnd || second_it != secondEnd) {
		if (*first_it != *second_it) {
			return false;
		}

		first_it++;
		second_it++;

		skipNonSignificant(first_it, firstEnd);
		skipNonSignificant(second_it, secondEnd);
	}

	return (first_it == firstEnd) && (second_it == secondEnd);
}
