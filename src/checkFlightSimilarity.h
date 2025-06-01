#pragma once

#include "flightClass/flight.h"

//#include <iostream>

inline bool checkFlightSimilarity(const std::string& flight1S, const std::string& flight2S) {
    const auto fl1 = flight::create(flight1S);
    const auto fl2 = flight::create(flight2S);

    return fl1 && fl2 && *fl1 == *fl2;

    /*const bool res = fl1 && fl2 && *fl1 == *fl2;

    std::cout << "checkFlightNumSimilarity(\"" << flight1S << "\", \"" << flight2S << "\") = "
            << (res ? "true" : "false") << std::endl;

    return res;*/
}