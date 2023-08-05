#pragma once
#include <SFML\Graphics.hpp>
#include <random>
#include <vector>
#include <cmath>
#include <utility>

#include "Grid.h"

using namespace sf;

class Simulation {
private:
    Grid grid;
    Font font;

public:
    // Constructor
    Simulation(int row_count, int col_count, float initial_wall_chance);

    // Check neighbours (update Cell's nextState)
    void prepareSingleCell(int x, int y);

    // Check all neighbours
    void prepareAllCells();

    // Update individual cell
    void updateSingleCell(int x, int y);

    // Update all cells
    void updateAllCells();

    // Scatter entities randomly across the grid
    void scatterSprinkles(int SprinkleCount);

    // Display grid
    void displayGrid(RenderWindow& window, int cellSize);
};
