#include "Grid.h"

Grid::Grid(int row_count, int col_count, float initial_wall_chance) : row_count(row_count), col_count(col_count) {
    grid.resize(row_count);
    for (auto& column : grid) {
        column.resize(col_count);
        for (auto& cell : column) {
            cell = std::make_unique<Cell>(utils::generateRandomWeightedBool(initial_wall_chance));
        }
    }
}


int Grid::getWidth() const { // Returns the number of columns in the grid (the grid's width)
    return this->col_count;
}

int Grid::getHeight() const { // Returns the number of rows in the grid (the grid's height)
    return this->row_count;
}


bool Grid::isWithinBounds(int x, int y) const { // Checks if the provided coordinates fall within the grid's boundaries
    return x >= 0 && x < col_count && y >= 0 && y < row_count;
}

// Returns a reference to the cell at the provided coordinates, or a nullopt if the coordinates are out of bounds
Cell* Grid::getCellAtCoords(int x, int y) {
    if (isWithinBounds(x, y)) {
        return grid[x][y].get();
    }
    else {
        return nullptr;
    }
}