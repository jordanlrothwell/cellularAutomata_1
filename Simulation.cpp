#include "Simulation.h"

Simulation::Simulation(int rows, int cols, float initialAliveCellPercentage)
	: grid(Grid(rows, cols, initialAliveCellPercentage)) {}

Grid& Simulation::currentGrid()
{
	return this->grid;
}

void Simulation::checkCellNeighbours(int x, int y)
{
	int wallCount = 0;

	for (int dx = -1; dx <= 1; dx++)
	{
		for (int dy = -1; dy <= 1; dy++)
		{
			int neighbourX = x + dx;
			int neighbourY = y + dy;

			if (grid.isWithinBoundary(neighbourX, neighbourY)) {
				if (grid.getCell(neighbourX, neighbourY).getIsWall()) {
					wallCount++;
				}
			}
			else {
				wallCount++; // Count boundary cells as walls
			}
		}
	}
	grid.getCell(x, y).setFutureState(wallCount > 4);
}


void Simulation::checkAllNeighbours()
{
	for (int i = 0; i < grid.getRows(); i++)
	{
		for (int j = 0; j < grid.getCols(); j++)
		{
			this->checkCellNeighbours(i, j);
		}
	}
}

void Simulation::updateCell(int x, int y)
{
	grid.getCell(x, y).updateCurrentState();
}

void Simulation::updateAllCells()
{
	for (int i = 0; i < grid.getRows(); i++)
	{
		for (int j = 0; j < grid.getCols(); j++)
		{
			this->updateCell(i, j);
		}
	}
}

void Simulation::scatterEntities(int SprinkleCount) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> disRow(0, grid.getRows() - 1);
	std::uniform_int_distribution<int> disCol(0, grid.getCols() - 1);

	for (int i = 0; i < SprinkleCount; ++i) {
		int randRow, randCol;

		// Keep generating random coordinates until an empty cell is found
		do {
			randRow = disRow(gen);
			randCol = disCol(gen);
		} while (grid.getCell(randRow, randCol).hasSprinkle());

		// Set Sprinkle
		Sprinkle* newSprinkle = new Sprinkle();
		grid.getCell(randRow, randCol).setSprinkle(newSprinkle);
	}
}

void Simulation::moveEntities() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(-1, 1);  // For generating random moves

	for (int i = 0; i < grid.getRows(); i++) {
		for (int j = 0; j < grid.getCols(); j++) {
			Cell& cell = grid.getCell(i, j);
			if (cell.hasSprinkle()) {
				int moveX = dis(gen);
				int moveY = dis(gen);
				int destX = i + moveX;
				int destY = j + moveY;

				// Check boundaries and if destination cell already has an Sprinkle or is a wall
				if (grid.isWithinBoundary(destX, destY) &&
					!grid.getCell(destX, destY).hasSprinkle() &&
					!grid.getCell(destX, destY).getIsWall()) {
					// Move Sprinkle
					Sprinkle* Sprinkle = cell.removeSprinkle(); // This should nullify the cell's Sprinkle pointer
					grid.getCell(destX, destY).setSprinkle(Sprinkle);
				}
			}
		}
	}
}



void Simulation::displayGrid(RenderWindow& window, int cellSize) {
	VertexArray pixels(Quads, grid.getRows() * grid.getCols() * 4);

	int index = 0;
	for (int i = 0; i < grid.getRows(); i++) {
		for (int j = 0; j < grid.getCols(); j++) {
			int x = j * cellSize;
			int y = i * cellSize;

			pixels[index + 0].position = Vector2f(x, y);
			pixels[index + 1].position = Vector2f(x + cellSize, y);
			pixels[index + 2].position = Vector2f(x + cellSize, y + cellSize);
			pixels[index + 3].position = Vector2f(x, y + cellSize);

			Cell& cell = grid.getCell(i, j);
			if (cell.getIsWall()) {
				pixels[index + 0].color = Color::Black;
				pixels[index + 1].color = Color::Black;
				pixels[index + 2].color = Color::Black;
				pixels[index + 3].color = Color::Black;
			}
			else if (cell.hasSprinkle()) {
				Color SprinkleColor = cell.getSprinkle()->getColor();
				pixels[index + 0].color = SprinkleColor;
				pixels[index + 1].color = SprinkleColor;
				pixels[index + 2].color = SprinkleColor;
				pixels[index + 3].color = SprinkleColor;
			}
			else {
				pixels[index + 0].color = Color::White;
				pixels[index + 1].color = Color::White;
				pixels[index + 2].color = Color::White;
				pixels[index + 3].color = Color::White;
			}

			index += 4;
		}
	}

	window.clear(sf::Color::White);
	window.draw(pixels);
	window.display();
}
