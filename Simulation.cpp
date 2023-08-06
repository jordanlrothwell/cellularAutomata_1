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
		int randRow = 0;
		int randCol = 0;
		do {
			randRow = disRow(gen);
			randCol = disCol(gen);
		} while (grid.getCellAtCoords(randRow, randCol) && (grid.getCellAtCoords(randRow, randCol)->hasSprinkle() || grid.getCellAtCoords(randRow, randCol)->hasWall()));

		std::unique_ptr<Sprinkle> newSprinkle = std::make_unique<Sprinkle>(randRow, randCol, 5);
		grid.getCellAtCoords(randRow, randCol)->placeSprinkle(std::move(newSprinkle));
	}
}

void Simulation::scatterFood(int food_count) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> disRow(0, grid.getWidth() - 1);
	std::uniform_int_distribution<int> disCol(0, grid.getHeight() - 1);

	for (int i = 0; i < food_count; ++i) {
		int randRow = 0;
		int randCol = 0;
		do {
			randRow = disRow(gen);
			randCol = disCol(gen);
		} while (grid.getCellAtCoords(randRow, randCol) && (grid.getCellAtCoords(randRow, randCol)->hasSprinkle() || grid.getCellAtCoords(randRow, randCol)->hasWall()));

		grid.getCellAtCoords(randRow, randCol)->placeFood();
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
						pixels[index + 0].color = Color::Red;
						pixels[index + 1].color = Color::Red;
						pixels[index + 2].color = Color::Red;
						pixels[index + 3].color = Color::Red;
						//ColourValue SprinkleColour = cell->getSprinkle()->getColour();
						//pixels[index + 0].color = { SprinkleColour.red, SprinkleColour.green, SprinkleColour.blue };
						//pixels[index + 1].color = { SprinkleColour.red, SprinkleColour.green, SprinkleColour.blue };
						//pixels[index + 2].color = { SprinkleColour.red, SprinkleColour.green, SprinkleColour.blue };
						//pixels[index + 3].color = { SprinkleColour.red, SprinkleColour.green, SprinkleColour.blue };
					}
					else if (cell->hasFood()) {
						pixels[index + 0].color = Color::Green;
						pixels[index + 1].color = Color::Green;
						pixels[index + 2].color = Color::Green;
						pixels[index + 3].color = Color::Green;
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

void Simulation::determineSprinkleDestination(Sprinkle& sprinkle)
{
	if (!sprinkle.isTravelling()) {
		std::queue<Coords> possible_destinations = sprinkle.getCoordsInRangeClosestToFurthest();
		std::priority_queue<PriorityCoords> prioritised_coords;
		std::set<Coords> occupied_coords;

		while (!possible_destinations.empty()) {
			Coords coords_being_checked = possible_destinations.front();
			possible_destinations.pop();
			if (grid.isWithinBounds(coords_being_checked.x, coords_being_checked.y)) {
				Cell& cell_at_destination = *grid.getCellAtCoords(coords_being_checked.x, coords_being_checked.y);
				if (cell_at_destination.hasWall() || cell_at_destination.hasSprinkle())
				{
					occupied_coords.insert(coords_being_checked);
				}
				else {
					PriorityCoords pc;
					pc.coord = coords_being_checked;
					pc.priority = cell_at_destination.hasFood() ? 2 : 1; // food has higher priority
					prioritised_coords.push(pc);
				}
			}
		}

		while (!prioritised_coords.empty()) {
			PriorityCoords destination_being_considered = prioritised_coords.top();
			prioritised_coords.pop();
			std::queue<Coords> coordsBetweenSprinkleAndCell = utils::bresenhamLine(sprinkle.getPosition().x, sprinkle.getPosition().y, destination_being_considered.coord.x, destination_being_considered.coord.y);

			bool pathIsClear = true; // assume the path is clear initially

			while (!coordsBetweenSprinkleAndCell.empty()) {
				Coords coord_on_path = coordsBetweenSprinkleAndCell.front();
				coordsBetweenSprinkleAndCell.pop();

				if (occupied_coords.find(coord_on_path) != occupied_coords.end()) {
					pathIsClear = false;
					break;
				}
			}

			if (pathIsClear) {
				sprinkle.setDestination(destination_being_considered.coord);
				return;
			}
		}
	}
}

void Simulation::setDestinationForAllSprinkles() {
	for (int x = 0; x < grid.getWidth(); x++)
	{
		for (int y = 0; y < grid.getHeight(); y++)
		{
			if (grid.getCellAtCoords(x, y)->hasSprinkle()) {
				Sprinkle* sprinkle = grid.getCellAtCoords(x, y)->getSprinkle();
				determineSprinkleDestination(*sprinkle);
			}
		}
	}
}

void Simulation::moveSprinkle(Sprinkle& sprinkle) {
	if (sprinkle.reachedDestination()) {
		sprinkle.setDestination(std::nullopt);
		grid.getCellAtCoords(sprinkle.getPosition().x, sprinkle.getPosition().y)->removeFood();
		return;
	}
	Coords next_move = sprinkle.getNextMove();
	Cell& target_cell = *grid.getCellAtCoords(next_move.x, next_move.y);
	if (target_cell.hasSprinkle()) {
		sprinkle.setDestination(std::nullopt);
		return;
	}
	Coords current_position = sprinkle.getPosition();
	Cell& current_cell = *grid.getCellAtCoords(current_position.x, current_position.y);
	std::unique_ptr<Sprinkle> sprinkle_ptr = current_cell.removeSprinkle();
	target_cell.placeSprinkle(std::move(sprinkle_ptr));
	sprinkle.setPosition(next_move.x, next_move.y);
}


void Simulation::moveAllSprinkles() {
	std::vector<std::pair<Sprinkle*, Coords>> moves; 

	for (int x = 0; x < grid.getWidth(); x++) {
		for (int y = 0; y < grid.getHeight(); y++) {
			if (grid.getCellAtCoords(x, y)->hasSprinkle()) {
				Sprinkle* sprinkle = grid.getCellAtCoords(x, y)->getSprinkle();
				Coords next_move = sprinkle->getNextMove();
				if (grid.getCellAtCoords(next_move.x, next_move.y)->hasSprinkle()) {
					sprinkle->setDestination(std::nullopt);
				}
				else {
					moves.push_back({ sprinkle, next_move });
				}
			}
		}
	}

	for (auto& move : moves) {
		Sprinkle* sprinkle = move.first;
		Coords& next_move = move.second;
		Coords current_position = sprinkle->getPosition();
		Cell& current_cell = *grid.getCellAtCoords(current_position.x, current_position.y);
		std::unique_ptr<Sprinkle> sprinkle_ptr = current_cell.removeSprinkle();
		Cell& target_cell = *grid.getCellAtCoords(next_move.x, next_move.y);
		target_cell.placeSprinkle(std::move(sprinkle_ptr));
		sprinkle->setPosition(next_move.x, next_move.y);
		if (sprinkle->reachedDestination()) {
			sprinkle->setDestination(std::nullopt);
			target_cell.removeFood();
		}
	}
}
