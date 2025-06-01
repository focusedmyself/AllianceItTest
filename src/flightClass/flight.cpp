#include "flight.h"

std::optional<std::string> flight::get_code() const {
    return code_;
}

std::uint32_t flight::get_number() const {
    return number_;
}

std::string flight::get_flight() const {
    if (style_ == style::ThreeLetters)
        return code_.value() + std::to_string(number_);
    if (style_ == style::TwoLettersSpace)
        return code_.value() + " " + std::to_string(number_);
    if (style_ == style::TwoLetters)
        return code_.value() + " " + std::to_string(number_);
    if (style_ == style::LetterNumSpace)
        return code_.value() + " " + std::to_string(number_);
    if (style_ == style::LetterNum)
        return code_.value() + " " + std::to_string(number_);
    return std::to_string(number_);
}

std::optional<flight> flight::create(const std::string& flightS) {
    return checkFlightCorrectness(flightS);
}

std::optional<flight> flight::checkFlightCorrectness(const std::string& flightS) {
    if (flightS.empty() || flightS.size() > 7)
        return std::nullopt;

    //std::cout << "length: " << flightS.length() << " " << flightS << "\n";

    const auto num_it = std::find_if(flightS.rbegin(), flightS.rend(), [](char c) -> bool {
            return !std::isdigit(c);
        });

    size_t num_start = std::distance(flightS.begin(), num_it.base());

    // specific A1 style case
    if (num_start == 1) {
        num_start = 2;
    }
    std::string number = flightS.substr(num_start);
    if (number.empty() || number.size() > 5)
        return std::nullopt;

    if (num_start == 0) {
        try {
            return flight(number, style::None);
        } catch (...) {
            return std::nullopt;
        }
    }

    std::string code = flightS.substr(0, num_start);
    const uint8_t codeSize = code.size();

    // [A-Z][A-Z][A-Z]
    if (codeSize == 3 && std::all_of(code.begin(), code.end(), isupper)) {
        return flight(number, style::ThreeLetters, code);
    }

    // [A-Z][A-Z] space
    if (codeSize == 3 && std::isupper(code[0]) && std::isupper(code[1]) && code[2] == ' ') {
        code.pop_back();
        try {
            return flight(number, style::TwoLettersSpace, code);
        } catch (...) {
            return std::nullopt;
        }
    }

    // [A-Z][A-Z]
    if (codeSize == 2 && std::all_of(code.begin(), code.end(), isupper)) {
        try {
            return flight(number, style::TwoLetters, code);
        } catch (...) {
            return std::nullopt;
        }
    }

    // [A-Z0-9][A-Z0-9] space, one letter min
    if (codeSize == 3 && std::isalnum(code[0]) && std::isalnum(code[1]) && code[2] == ' ' && (isupper(code[0]) || isupper(code[1]))) {
        code.pop_back();
        try {
            return flight(number, style::LetterNumSpace, code);
        } catch (...) {
            return std::nullopt;
        }
    }

    // [A-Z0-9][A-Z0-9], one letter min
    if (codeSize == 2 && std::isalnum(code[0]) && std::isalnum(code[1]) && (isupper(code[0]) || isupper(code[1]))) {
        try {
            return flight(number, style::LetterNum, code);
        } catch (...) {
            return std::nullopt;
        }
    }
    return std::nullopt;
}