#include <unordered_set>
#include <string>
#include <fstream>
#include <iostream>

#include "utility/flightUtility.h"

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
		catch (const std::length_error& e) {
			continue;
		}
	}
}