#include "Automaton.h"

// Constructor
Automaton::Automaton(int rows, int cols, float initialAliveCellPercentage)
	: gridInstance(Grid(rows, cols, initialAliveCellPercentage))
{

}

Grid& Automaton::currentGrid()
{
	return this->gridInstance;
}

void Automaton::checkCellNeighbours(int x, int y)
{
	int wallCount = 0;

	for (int dx = -1; dx <= 1; dx++)
	{
		for (int dy = -1; dy <= 1; dy++)
		{
			int neighbourX = x + dx;
			int neighbourY = y + dy;

			if (gridInstance.isWithinBoundary(neighbourX, neighbourY)) {
				if (gridInstance.getCell(neighbourX, neighbourY).isWall()) {
					wallCount++;
				}
			}
			else {
				wallCount++; // Count boundary cells as walls
			}
		}
	}

	// Apply the rule here after counting neighbors
	if (wallCount > 4)
	{
		gridInstance.getCell(x, y).setNextState(1);
	}
	else
	{
		gridInstance.getCell(x, y).setNextState(0);
	}
}


void Automaton::checkAllNeighbours()
{
	for (int i = 0; i < gridInstance.getRows(); i++)
	{
		for (int j = 0; j < gridInstance.getCols(); j++)
		{
			this->checkCellNeighbours(i, j);
		}
	}
}

void Automaton::updateCell(int x, int y)
{
	gridInstance.getCell(x, y).updateState();
}

void Automaton::updateAllCells()
{
	for (int i = 0; i < gridInstance.getRows(); i++)
	{
		for (int j = 0; j < gridInstance.getCols(); j++)
		{
			this->updateCell(i, j);
		}
	}
}

void Automaton::displayGrid(RenderWindow& window, int cellSize)
{
	VertexArray pixels(Quads, gridInstance.getRows() * gridInstance.getCols() * 4);

	int index = 0;
	for (int i = 0; i < gridInstance.getRows(); i++)
	{
		for (int j = 0; j < gridInstance.getCols(); j++)
		{
			int x = j * cellSize;
			int y = i * cellSize;

			pixels[index + 0].position = Vector2f(x, y);
			pixels[index + 1].position = Vector2f(x + cellSize, y);
			pixels[index + 2].position = Vector2f(x + cellSize, y + cellSize);
			pixels[index + 3].position = Vector2f(x, y + cellSize);

			if (gridInstance.getCell(i, j).isWall())
			{
				pixels[index + 0].color = Color::Black;
				pixels[index + 1].color = Color::Black;
				pixels[index + 2].color = Color::Black;
				pixels[index + 3].color = Color::Black;
			}
			else
			{
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
