#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Grid.h"

using namespace sf;

class Simulation {
private:
    Grid grid;

public:
    // Constructor
    Simulation(int rows, int cols, float initialAliveCellPercentage);

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

    // Move entities
    void moveSprinkles();

    // Display grid
    void displayGrid(RenderWindow& window, int cellSize);
};