#include <string>
#include <vector>
#include <thread>
#include <iostream>

#include "checkFlightSimilarity.h"
#include "removeNonUniqueFlights.h"
#include "utility/flightUtility.h"

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
			bool res = checkFlightSimilarty(a, b);
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

