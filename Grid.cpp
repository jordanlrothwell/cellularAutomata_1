#include "Grid.h"

// Constructor
Grid::Grid(int rowsParam, int colsParam, float initialAliveCellPercentage)
	: rows(rowsParam), cols(colsParam) {
	grid.resize(rows);

	for (int i = 0; i < rows; i++) {
		grid[i].resize(cols);
		for (int j = 0; j < cols; j++) {
			bool initialState = generateRandomBool(initialAliveCellPercentage);
			grid[i][j] = std::make_unique<Cell>(initialState);
		}
	}
}

bool Grid::generateRandomBool(float distributionParam)
{
	static std::random_device seed;
	static std::mt19937 randomNumberFromSeed(seed());
	std::bernoulli_distribution weightedDistributionZeroToOne(distributionParam);

	return weightedDistributionZeroToOne(randomNumberFromSeed);
}

int Grid::getRows()
{
	return this->rows;
}

int Grid::getCols()
{
	return this->cols;
}

bool Grid::isWithinBoundary(int x, int y)
{
	if (0 <= x && x < this->cols) {
		if (0 <= y && y < this->rows) {
			return true;
		}
	}
	return false;
}

Cell& Grid::getCell(int x, int y) const
{
	return *(grid[x][y]);
}

bool Grid::isValidMove(int x, int y) const {
	if (0 <= x && x < this->cols && 0 <= y && y < this->rows) {
		if (!getCell(x, y).getIsWall()) {
			return true;
		}
	}
	return false;
}

