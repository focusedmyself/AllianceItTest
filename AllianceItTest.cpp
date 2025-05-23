#include <string>
#include <vector>
#include <thread>
#include <fstream>
#include <unordered_set>
#include <iostream>

bool checkFlightNumSimilarty(const std::string& c_first, const std::string& c_second);
std::string normalizeFlight(const std::string& flight);
void removeNonUniqueFlights(const std::string& inFilename, const std::string& outFilename);

int main()
{
	std::pair<std::string, std::string> tests[] = {
			{"AFL1",    "AFL0001"},
			{"D2 25",   "D225"},
			{"D2025",   "D2025"},
			{"AFL1",    "D2025"},
			{"AB 005",  "AB5"},
			{"S7  123", "S7123"},
			{"UT123",   "UT0123"},
			{"SU001",   "SU1"},
			{"ABC 000", "ABC0"},
			{"XYZ",     "XYZ000"},
			{"X 07",     "X7"}
	};

	try {
		for (const auto& [a, b] : tests) {
			bool res = checkFlightNumSimilarty(a, b);
			std::cout << "checkFlightNumSimilarty(\"" << a << "\", \"" << b << "\") = "
				<< (res ? "true" : "false") << std::endl;
		}
	}
	catch (const std::length_error& e) {
		std::cerr << "Caught std::length_error: " << e.what();
	}

	std::vector<std::string> testFlights = {
		"AB12", "AB012", "22", "AA", "AFL 0001", "S7 0123", "AB 005", "  007", "SU123", "A1 0002",
		"AA123", "ABC123", "00123", "  000", "A0", "A 0001", "ABCD12345"
	};

	for (const auto& flight : testFlights) {
		try {
			std::cout << "In: [" << flight << "]"
				<< "  Out: [" << normalizeFlight(flight) << "]\n";
		}
		catch (const std::exception& e) {
			std::cout << "In: [" << flight << "]"
				<< "  Error: " << e.what() << "\n";
		}
	}

	std::thread t1(removeNonUniqueFlights, "1_in.txt", "1_out.txt");
	std::thread t2(removeNonUniqueFlights, "2_in.txt", "2_out.txt");

	t1.join();
	t2.join();

	return 0;

}

// Version 1 slower coz exception

bool checkFlightNumSimilarty(const std::string& c_first, const std::string& c_second) 
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

bool checkFlightNumSimilarty(const std::string& c_first, const std::string& c_second, std::string& error) noexcept
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

void removeNonUniqueFlights(const std::string& inFilename, const std::string& outFilename) {
	std::ifstream in(inFilename);
	if (!in) {
		std::cerr << "Cant open: " << inFilename << std::endl;
		return;
	}
	std::ofstream out(outFilename);
	if (!out) {
		std::cerr << "Cant create: " << outFilename << std::endl;
		return;
	}

	std::unordered_set<std::string> uniqueFlights{};
	std::string line{};

	while (std::getline(in, line)) {
		try {
			if (uniqueFlights.insert(normalizeFlight(line)).second) {
				out << line << "\n";
			}
		}
		catch (const std::length_error& e){
			continue;
		}
	}
}	