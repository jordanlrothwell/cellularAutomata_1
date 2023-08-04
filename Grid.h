#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <memory>
#include "Cell.h"

class Grid {
private:
    int rows;
    int cols;
    std::vector<std::vector<std::unique_ptr<Cell>>> grid;

public:
    Grid(int rowsParam, int colsParam, float initialAliveCellPercentage);

    bool generateRandomBool(float distributionParam);

    int getRows();

    int getCols();

    bool isWithinBoundary(int x, int y);

    Cell& getCell(int x, int y) const;

    bool isValidMove(int x, int y) const;
};
