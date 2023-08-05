#include "Simulation.h"

Simulation::Simulation(int row_count, int col_count, float initial_wall_chance)
	: grid(Grid(row_count, col_count, initial_wall_chance)) {}

void Simulation::prepareSingleCell(int x, int y) {
	Cell* cell = grid.getCellAtCoords(x, y);

	if (cell) {
		int wall_count = 0;

		for (int dx = -1; dx <= 1; dx++) {
			for (int dy = -1; dy <= 1; dy++) {
				int neighbour_x = x + dx;
				int neighbour_y = y + dy;
				if (grid.isWithinBounds(neighbour_x, neighbour_y)) {
					Cell* neighbour_cell = grid.getCellAtCoords(neighbour_x, neighbour_y);
					if (neighbour_cell && neighbour_cell->hasWall()) {
						wall_count++;
					}
				}
				else {
					wall_count++;
				}
			}
		}
		cell->setFutureWallState(wall_count > 4);
	}
}

void Simulation::prepareAllCells()
{
	for (int x = 0; x < grid.getWidth(); x++)
	{
		for (int y = 0; y < grid.getHeight(); y++)
		{
			this->prepareSingleCell(x, y);
		}
	}
}

void Simulation::updateSingleCell(int x, int y)
{
	Cell* cell = grid.getCellAtCoords(x, y);
	if (cell) {
		cell->updateCurrentWallState();
	}
}


void Simulation::updateAllCells()
{
	for (int x = 0; x < grid.getWidth(); x++)
	{
		for (int y = 0; y < grid.getHeight(); y++)
		{
			this->updateSingleCell(x, y);
		}
	}
}

void Simulation::scatterSprinkles(int SprinkleCount) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> disRow(0, grid.getWidth() - 1);
	std::uniform_int_distribution<int> disCol(0, grid.getHeight() - 1);

	for (int i = 0; i < SprinkleCount; ++i) {
		int randRow, randCol;
		do {
			randRow = disRow(gen);
			randCol = disCol(gen);
		} while (grid.getCellAtCoords(randRow, randCol) && grid.getCellAtCoords(randRow, randCol)->hasSprinkle());

		std::unique_ptr<Sprinkle> newSprinkle = std::make_unique<Sprinkle>(randRow, randCol, 5);
		grid.getCellAtCoords(randRow, randCol)->placeSprinkle(std::move(newSprinkle));
	}
}

void Simulation::displayGrid(RenderWindow& window, int cellSize) {
	VertexArray pixels(Quads, grid.getWidth() * grid.getHeight() * 4);

	int index = 0;
	for (int i = 0; i < grid.getWidth(); i++) {
		for (int j = 0; j < grid.getHeight(); j++) {
			int x = static_cast<int>(i * cellSize);
			int y = static_cast<int>(j * cellSize);

			pixels[index + 0].position = Vector2f(static_cast<float>(x), static_cast<float>(y));
			pixels[index + 1].position = Vector2f(static_cast<float>(x + cellSize), static_cast<float>(y));
			pixels[index + 2].position = Vector2f(static_cast<float>(x + cellSize), static_cast<float>(y + cellSize));
			pixels[index + 3].position = Vector2f(static_cast<float>(x), static_cast<float>(y + cellSize));

			Cell* cell = grid.getCellAtCoords(i, j);
			if (cell) {
				if (cell->hasWall()) {
					pixels[index + 0].color = Color::Black;
					pixels[index + 1].color = Color::Black;
					pixels[index + 2].color = Color::Black;
					pixels[index + 3].color = Color::Black;
				}
				else if (cell->hasSprinkle()) {
					ColourValue SprinkleColour = cell->getSprinkle()->getColour();
					pixels[index + 0].color = { SprinkleColour.red, SprinkleColour.green, SprinkleColour.blue };
					pixels[index + 1].color = { SprinkleColour.red, SprinkleColour.green, SprinkleColour.blue };
					pixels[index + 2].color = { SprinkleColour.red, SprinkleColour.green, SprinkleColour.blue };
					pixels[index + 3].color = { SprinkleColour.red, SprinkleColour.green, SprinkleColour.blue };
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
	}

	window.clear(sf::Color::White);
	window.draw(pixels);
	window.display();
}
