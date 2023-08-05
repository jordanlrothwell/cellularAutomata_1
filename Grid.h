#pragma once    
#include <vector> 
#include "Cell.h"

class Grid {
private:
    // Data members
    int row_count;
    int col_count;
    std::vector<std::vector<std::unique_ptr<Cell>>> grid;

public:
    // Constructors
    Grid(int row_count, int col_count, float initial_wall_chance);

    // Getter methods
    int getWidth() const;
    int getHeight() const;

    // Utility methods
    bool isWithinBounds(int x, int y) const;

    // Cell access method
    Cell* getCellAtCoords(int x, int y);
};
