#include <string>
#include <thread>

#include "checkFlightSimilarity.h"
#include "removeNonUniqueFlights.h"

int main()
{
	std::pair<std::string, std::string> tests[] = {
			{"AFL1",    "AFL0001"},
			{"D2 25",   "D225"},
			{"D2025",   "D2025"},
			{"AFL1",    "D2025"},
			{"AB 005",  "AB5"},
			{"S7 123", "S7123"},
			{"UT123",   "UT0123"},
			{"SU001",   "SU1"},
			{"ABC 001", "ABC1"},
			{"XYZ",     "XYZ001"},
			{"XR 07",     "X7"}
	};

	for (const auto& [flight1, flight2] : tests) {
		checkFlightSimilarity(flight1, flight2);
	}

	std::thread t1(removeNonUniqueFlights, "1_in.txt", "1_out.txt");
	std::thread t2(removeNonUniqueFlights, "2_in.txt", "2_out.txt");

	t1.join();
	t2.join();

	return 0;
}

