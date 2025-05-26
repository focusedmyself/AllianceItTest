#pragma once

#include <string>

std::string normalizeFlight(const std::string& flight)
{
	if (flight.empty()) {
		return flight;
	}

	uint8_t flightNameLen = flight.size();

	if (flightNameLen > 7) {
		throw std::length_error("");
	}

	std::string code{}, number{};

	if (flightNameLen == 1) {
		if (std::isdigit(flight[0]))
			return flight;
		throw std::invalid_argument("");
	}

	auto removeLeadingZerosAndSpaces = [](const std::string s) {
		if (s.empty())
			return s;

		size_t firstNonSpace = s.find_first_not_of(' ');
		size_t firstNonZero = s.find_first_not_of('0', firstNonSpace);

		if (firstNonZero == std::string::npos)
			return std::string();

		return s.substr(firstNonZero);
		};

	// Only for 2D and D2 style (num + letter)
	if (std::isdigit(flight[0]) != std::isdigit(flight[1])) {
		code = flight.substr(0, 2);
		number = removeLeadingZerosAndSpaces(flight.substr(2));
		return code + number;
	}

	if (flightNameLen < 3) {
		return removeLeadingZerosAndSpaces(flight);
	}

	if (!std::isalpha(flight[2]) && std::isalpha(flight[0]) && std::isalpha(flight[1])) {
		code = flight.substr(0, 2);
		number = removeLeadingZerosAndSpaces(flight.substr(2));
		return code + number;
	}

	if (std::isalpha(flight[2])) {
		code = flight.substr(0, 3);
		number = removeLeadingZerosAndSpaces(flight.substr(3));
		return code + number;
	}

	return removeLeadingZerosAndSpaces(flight);
}