#include "Simulation.h"

const float BIRTH_RATE = 1.2f;  // Expected number of children over entire fertility period
const int FERTILE_AGE = 200;  // Age at which a sprinkle starts to be fertile
const int DEATH_AGE = 1000;  // Age at which a sprinkle dies

Simulation::Simulation(int rows, int cols, float initialAliveCellPercentage, int windowWidth)
	: grid(Grid(rows, cols, initialAliveCellPercentage)) {
	if (!font.loadFromFile("font.ttf")) {
	std::cout << "Missing font file!";
	}
}

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
				if (grid.getCell(neighbourX, neighbourY).isWall()) {
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

		std::unique_ptr<Sprinkle> newSprinkle = std::make_unique<Sprinkle>(randRow, randCol, 10);
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
			if (cell.isWall()) {
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

void Simulation::chooseSprinkleDestinations() {
	for (int i = 0; i < grid.getRows(); i++) {
		for (int j = 0; j < grid.getCols(); j++) {
			Cell& cell = grid.getCell(i, j);
			if (cell.hasSprinkle()) {
				Sprinkle* sprinkle = cell.getSprinkle();
				std::pair<int, int> destination = this->chooseDestination(*sprinkle);
				sprinkle->setCurrentDestination(destination);
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

				if (sprinkle->getAge() > DEATH_AGE)
				{
					killSprinkle(*sprinkle);
				}
			}
		}
	}
}


void Simulation::reproduceSprinkles() {
	float fertility_period = DEATH_AGE - FERTILE_AGE;
	float yearly_reproduction_chance = BIRTH_RATE / fertility_period;

	for (int i = 0; i < grid.getRows(); i++) {
		for (int j = 0; j < grid.getCols(); j++) {
			Cell& cell = grid.getCell(i, j);
			if (cell.hasSprinkle()) {
				Sprinkle* sprinkle = cell.getSprinkle();
				if (sprinkle->getAge() > FERTILE_AGE && sprinkle->getAge() < DEATH_AGE) {
					std::random_device rd;
					std::mt19937 gen(rd());
					std::uniform_real_distribution<float> dis(0.0f, 1.0f);

					if (dis(gen) < yearly_reproduction_chance) {
						std::vector<std::pair<int, int>> potentialLocations;

						// Collect potential offspring locations
						for (int dx = -1; dx <= 1; dx++) {
							for (int dy = -1; dy <= 1; dy++) {
								if (grid.isWithinBoundary(i + dx, j + dy)) {
									Cell& newCell = grid.getCell(i + dx, j + dy);
									if (!newCell.isWall() && !newCell.hasSprinkle()) {
										potentialLocations.push_back(std::make_pair(i + dx, j + dy));
									}
								}
							}
						}

						// Choose a random location for the offspring
						if (!potentialLocations.empty()) {
							std::uniform_int_distribution<int> dis_loc(0, potentialLocations.size() - 1);
							std::pair<int, int> location = potentialLocations[dis_loc(gen)];
							int x = location.first;
							int y = location.second;

							Cell& offspringCell = grid.getCell(x, y);
							sf::Color parentColor = sprinkle->getColor();
							std::unique_ptr<Sprinkle> newSprinkle = std::make_unique<Sprinkle>(x, y, parentColor.r, parentColor.g, parentColor.b, 10);
							offspringCell.setSprinkle(std::move(newSprinkle));

						}
					}
				}
			}
		}
	}
}

std::queue<std::pair<int, int>> Simulation::getCoordinatesInSightRange(Sprinkle& sprinkle) {
	std::queue<std::pair<int, int>> coordinatesInSightRange; // queue to store coords in range
	std::set<std::pair<int, int>> blockedCoordinates; // set to store occupied coords (more efficient lookup)

	for (int cellsAway = 1; cellsAway <= sprinkle.getSightRange(); cellsAway++) {
		for (int dx = -cellsAway; dx < cellsAway; dx++) {
			for (int dy = -cellsAway; dy < cellsAway; dy++) {

				int x = sprinkle.getPosition().first;
				int y = sprinkle.getPosition().second;

				if (!grid.isWithinBoundary(x, y) || blockedCoordinates.find({ x, y }) != blockedCoordinates.end()) { // skip coords if outside boundary or already blocked
					break;
				}

				Cell& cellAtCoords = grid.getCell(x, y);

				if (cellAtCoords.isWall() || cellAtCoords.hasSprinkle()) { // if the potential cell is occupied

					blockedCoordinates.insert({ x, y }); // add its coordinates to the set

					std::pair<int, int> furthestPointOnTheLine = getFurthestPointOnTheLine(sprinkle.getPosition(), { x, y }, sprinkle.getSightRange()); // get the furthest point (which the sprinkle can see) on the line passing through its current position and the one it just found (which was occupied)

					// assigns for bresenham's line algorithm
					int x0 = furthestPointOnTheLine.first;
					int y0 = furthestPointOnTheLine.second;
					int dx = abs(x - x0);
					int dy = abs(y - y0);
					int sx = (x0 < x) ? 1 : -1;
					int sy = (y0 < y) ? 1 : -1;
					int err = dx - dy;

					while (x0 != x || y0 != y) {
						blockedCoordinates.insert({ x0, y0 }); // add its coordinates to the set
						int e2 = 2 * err;
						if (e2 > -dy) {
							err -= dy;
							x0 += sx;
						}
						if (e2 < dx) {
							err += dx;
							y0 += sy;
						}
					}
				}
				else {
					coordinatesInSightRange.push({ x, y }); // if not occupied or blocked, add to queue
				}
			}
		}
	}

	return coordinatesInSightRange;
}

std::pair<int, int> Simulation::getFurthestPointOnTheLine(std::pair<int, int> origin, std::pair<int, int> pointOnTheLine, int distance)
{
	// direction vectors
	int dx = pointOnTheLine.first - origin.first; // = x2 - x1
	int dy = pointOnTheLine.second - origin.second; // = y2 - y1
	
	double length = std::sqrt(dx * dx + dy * dy); // length of the direction vector
	
	// normalise direction vector to get unit vector
	int scale = 10000; // multiply by a large scale factor to preserve precision
	int unit_dx = static_cast<int>(dx / length * scale);
	int unit_dy = static_cast<int>(dy / length * scale);

	// scale the unit vector by the distance
	// divide by the scale factor to get back to the original scale
	int displacement_dx = unit_dx * distance / scale;
	int displacement_dy = unit_dy * distance / scale;

	// calculate the new end point
	int new_x = pointOnTheLine.first + displacement_dx;
	int new_y = pointOnTheLine.second + displacement_dy;

	return { new_x, new_y };
}

std::pair<int, int> Simulation::chooseDestination(Sprinkle& sprinkle) {

	if (!sprinkle.isTravelling()) { // keep current destination if sprinkle is already travelling

		sprinkle.setTravelling(true); // put sprinkle into travelling state

		std::queue<std::pair<int, int>> coordinatesInSightRange = getCoordinatesInSightRange(sprinkle);
		std::vector<std::pair<int, int>> allCoordinates;

		while (!coordinatesInSightRange.empty()) {
			std::pair<int, int> currentlyEvaluating = coordinatesInSightRange.front();
			coordinatesInSightRange.pop();

			allCoordinates.push_back(currentlyEvaluating);
		}

		// Pick a random coordinate
		if (!allCoordinates.empty()) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> distrib(0, allCoordinates.size() - 1);

			int randomIndex = distrib(gen);
			return allCoordinates[randomIndex];
		}


		
		return sprinkle.getPosition(); // if no valid coordinate was found, return the sprinkle's current position as a fallback
	}
}
