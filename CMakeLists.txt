cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME AllianceItTest)

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} "src/AllianceItTest.cpp"
        src/flightClass/flight.cpp
        src/flightClass/flight.h
        src/checkFlightSimilarity.h
        src/removeNonUniqueFlights.h)
