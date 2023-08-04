#pragma once
#include <SFML\Graphics.hpp>
#include <random>
#include <vector>
#include <cmath>
#include <utility>

#include "Grid.h"
#include "Cell.h"

using namespace sf;

struct ColorComparator {
    bool operator() (const sf::Color& color1, const sf::Color& color2) const {
        if (color1.r != color2.r) return color1.r < color2.r;
        if (color1.g != color2.g) return color1.g < color2.g;
        return color1.b < color2.b;
    }
};

class Simulation {
private:
    Grid grid;
    Font font;

public:
    // Constructor
    Simulation(int rows, int cols, float initialAliveCellPercentage, int windowWidth);

    // Return grid instance
    Grid& currentGrid();

    // Check neighbours (update Cell's nextState)
    void checkCellNeighbours(int x, int y);

    // Check all neighbours
    void checkAllNeighbours();

    // Update individual cell
    void updateCell(int x, int y);

    // Update all cells
    void updateAllCells();

    // Scatter entities randomly across the grid
    void scatterSprinkles(int SprinkleCount);

    void chooseSprinkleDestinations();

    void moveSprinkleIfValid(Sprinkle& sprinkle, int newX, int newY);

    // Move sprinkles
    void moveSprinkles();

    // Display grid
    void displayGrid(RenderWindow& window, int cellSize);

    Cell& getSprinkleCell(Sprinkle& sprinkle);

    void killSprinkle(Sprinkle& sprinkle);

    void pruneMatureSprinkles();

    void reproduceSprinkles();

    std::queue<std::pair<int, int>> getCoordinatesInSightRange(Sprinkle& sprinkle);

    std::pair<int, int> getFurthestPointOnTheLine(std::pair<int, int> origin, std::pair<int, int> pointOnTheLine, int distance);

    std::pair<int, int> chooseDestination(Sprinkle& sprinkle);
};