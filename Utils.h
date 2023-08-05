#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <optional>


// A struct to hold RGB values
struct ColourValue {
    sf::Uint8 red;
    sf::Uint8 green;
    sf::Uint8 blue;

    // Constructor
    ColourValue(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b) : red(r), green(g), blue(b) {}
};

struct Coords {
    int x;
    int y;
};

namespace utils {
    bool generateRandomWeightedBool(float trueProbability);
    ColourValue generateRandomColorValue();
};

using OptionalCoords = std::optional<Coords>;