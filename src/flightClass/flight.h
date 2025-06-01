#ifndef FLIGHT_H
#define FLIGHT_H
#include <string>
#include <optional>

class flight {
public:
    enum class style {
        ThreeLetters,
        TwoLettersSpace,
        TwoLetters,
        LetterNum,
        LetterNumSpace,
        None
    };

    static std::optional<flight> checkFlightCorrectness(const std::string& flightS);
    static std::optional<flight> create(const std::string& flightS);

    std::optional<std::string> get_code() const;
    std::uint32_t get_number() const;
    std::string get_flight() const;

    bool operator==(const flight& other) const {
        return code_ == other.code_ && number_ == other.number_;
    }

    flight() = default;
    flight(const flight&) = default;
    flight(flight&&) = default;
    flight& operator=(const flight&) = default;
    flight& operator=(flight&&) = default;
    ~flight() = default;
private:
    template <typename NumberT,
            std::enable_if_t<
              std::is_same_v<NumberT, std::string> ||
              std::is_same_v<NumberT, std::uint32_t>, int> = 0>
    flight(NumberT number, style style, std::optional<std::string> code = std::nullopt);

    std::optional<std::string> code_;
    std::uint32_t number_;
    style style_ = style::ThreeLetters;
};

template<typename NumberT,
                std::enable_if_t<
                  std::is_same_v<NumberT, std::string> ||
                  std::is_same_v<NumberT, std::uint32_t>, int>>

flight::flight(NumberT number, const style style, const std::optional<std::string> code)
    : code_(std::move(code)), style_(style)
{
    if constexpr (std::is_same_v<NumberT, std::string>) {
        try {
            this->number_ = static_cast<std::uint32_t>(std::stoul(number));
        } catch (...) {
            throw std::invalid_argument("Currently flight number can only be std::string or std::uint32_t");
        }
    } else if constexpr (std::is_same_v<NumberT, std::uint32_t>) {
        this->number_ = number;
    } else {
        static_assert(!std::is_same_v<NumberT, NumberT>, "Currently flight number can only be std::string or std::uint32_t");
    }
}

namespace std {
    template <>
    struct hash<flight> {
        std::size_t operator()(const flight& f) const {
            const std::size_t h1 = std::hash<std::string>{}(f.get_code().value_or(""));
            const std::size_t h2 = std::hash<std::uint32_t>{}(f.get_number());
            return h1 ^ (h2 << 1);
        }
    };
}

#endif //FLIGHT_H
