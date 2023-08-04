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
				wallCount++;
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

void Simulation::scatterSprinkles(int SprinkleCount) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> disRow(0, grid.getRows() - 1);
	std::uniform_int_distribution<int> disCol(0, grid.getCols() - 1);

	for (int i = 0; i < SprinkleCount; ++i) {
		int randRow, randCol;
		do {
			randRow = disRow(gen);
			randCol = disCol(gen);
		} while (grid.getCell(randRow, randCol).hasSprinkle());

		std::unique_ptr<Sprinkle> newSprinkle = std::make_unique<Sprinkle>(randRow, randCol);
		grid.getCell(randRow, randCol).setSprinkle(std::move(newSprinkle));
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

void Simulation::moveSprinkleIfValid(Sprinkle& sprinkle, int newX, int newY) {
	int oldX = sprinkle.getPosition().first;
	int oldY = sprinkle.getPosition().second;

	newX = std::max(0, std::min(grid.getRows() - 1, newX));
	newY = std::max(0, std::min(grid.getCols() - 1, newY));

	if (grid.isValidMove(newX, newY) && !grid.getCell(newX, newY).hasSprinkle()) {
		Cell& oldCell = grid.getCell(oldX, oldY);
		Cell& newCell = grid.getCell(newX, newY);

		std::unique_ptr<Sprinkle> sprinklePtr = oldCell.removeSprinkle();
		newCell.setSprinkle(std::move(sprinklePtr));

		sprinkle.setPosition(newX, newY);
	}
}


void Simulation::moveSprinkles() {
	for (int i = 0; i < grid.getRows(); i++) {
		for (int j = 0; j < grid.getCols(); j++) {
			Cell& cell = grid.getCell(i, j);
			if (cell.hasSprinkle()) {
				Sprinkle* sprinkle = cell.getSprinkle();

				sprinkle->increaseAge();

				std::pair<int, int> newPosition = sprinkle->move();
				int newX = newPosition.first;
				int newY = newPosition.second;

				moveSprinkleIfValid(*sprinkle, newX, newY);
			}
		}
	}
}

Cell& Simulation::getSprinkleCell(Sprinkle& sprinkle) {
	std::pair<int, int> position = sprinkle.getPosition();
	int x = position.first;
	int y = position.second;
	return grid.getCell(x, y);
}

void Simulation::killSprinkle(Sprinkle& sprinkle) {
	Cell& cell = getSprinkleCell(sprinkle);
	cell.removeSprinkle();
}

void Simulation::pruneMatureSprinkles() {
	for (int i = 0; i < grid.getRows(); i++) {
		for (int j = 0; j < grid.getCols(); j++) {
			Cell& cell = grid.getCell(i, j);
			if (cell.hasSprinkle()) {
				Sprinkle* sprinkle = cell.getSprinkle();

				if (sprinkle->getAge() > 100)
				{
					killSprinkle(*sprinkle);
				}
			}
		}
	}
}

void Simulation::reproduceSprinkles() {
	for (int i = 0; i < grid.getRows(); i++) {
		for (int j = 0; j < grid.getCols(); j++) {
			Cell& cell = grid.getCell(i, j);
			if (cell.hasSprinkle()) {
				Sprinkle* sprinkle = cell.getSprinkle();
				if (sprinkle->getAge() > 50 && sprinkle->getAge() < 100) {
					std::random_device rd;
					std::mt19937 gen(rd());
					std::uniform_int_distribution<int> dis(1, 20);

					if (dis(gen) == 20) {
						// Try to create a new sprinkle in an adjacent cell
						for (int dx = -1; dx <= 1; dx++) {
							for (int dy = -1; dy <= 1; dy++) {
								if (grid.isWithinBoundary(i + dx, j + dy)) {
									Cell& newCell = grid.getCell(i + dx, j + dy);
									if (!newCell.getIsWall() && !newCell.hasSprinkle()) {
										sf::Color parentColor = sprinkle->getColor();
										newCell.setSprinkle(std::make_unique<Sprinkle>(i + dx, j + dy, parentColor.r, parentColor.g, parentColor.b));
										return;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
