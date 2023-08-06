#include "Utils.h"

// Generates a random weighted boolean value
bool utils::generateRandomWeightedBool(float trueProbability)
{
    static std::random_device randomDevice;  // Initialize a random device
    static std::mt19937 randomEngine(randomDevice());  // Initialize a random engine using the random device
    std::bernoulli_distribution distribution(trueProbability);  // Initialize a Bernoulli distribution with the given true probability
    return distribution(randomEngine);  // Return a random boolean based on the distribution and engine
}

// Return a ColorValue with random RGB values
ColourValue utils::generateRandomColorValue()
{
    static std::random_device randomDevice; 
    static std::mt19937 randomEngine(randomDevice());  
    std::uniform_int_distribution<int> distribution(0, 255); 
    return ColourValue(distribution(randomEngine), distribution(randomEngine), distribution(randomEngine)); 
}

// Generates a random number in the range [min, max]
int utils::generateRandomInRange(int min, int max)
{
    static std::random_device randomDevice;
    static std::mt19937 randomEngine(randomDevice());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(randomEngine);
}

std::queue<Coords> utils::bresenhamLine(int x1, int y1, int x2, int y2)
{
    std::queue<Coords> lineCoords;

    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (true) {
        lineCoords.push({ x1, y1 });

        if (x1 == x2 && y1 == y2) {
            break;
        }

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }

    return lineCoords;
}