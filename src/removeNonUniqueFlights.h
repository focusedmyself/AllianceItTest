#include <unordered_set>
#include <string>
#include <fstream>
#include <iostream>

#include "flightClass/flight.h"

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

	std::unordered_set<flight> uniqueFFlights{};
	std::string line{};

	while (std::getline(in, line)) {
		line.erase(
		std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) {
					return !std::isspace(ch);
			}).base(),
			line.end()
			);
		const auto flight = flight::create(line);
		if (flight) {
			if (uniqueFFlights.insert(flight.value()).second) {
				out << flight.value().get_flight() << "\n";
			}
		}
	}
}
