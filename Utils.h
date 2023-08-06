#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <optional>
#include <queue>
#include <cmath>

// A struct to hold RGB values
struct ColourValue {
    sf::Uint8 red;
    sf::Uint8 green;
    sf::Uint8 blue;

    // Constructor
    ColourValue(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b) : red(r), green(g), blue(b) {}
};

struct Coords {
    int x, y;

    bool operator<(const Coords& other) const {
        if (x == other.x) {
            return y < other.y;
        }
        return x < other.x;
    }
};

struct PriorityCoords {
    Coords coord;
    int priority; // Higher value means higher priority

    bool operator<(const PriorityCoords& other) const {
        return priority < other.priority; // For max-heap behavior in std::priority_queue
    }
};

namespace utils {
    bool generateRandomWeightedBool(float trueProbability);
    ColourValue generateRandomColorValue();
    int generateRandomInRange(int min, int max);
    std::queue<Coords> bresenhamLine(int x1, int y1, int x2, int y2);
};

using OptionalCoords = std::optional<Coords>;