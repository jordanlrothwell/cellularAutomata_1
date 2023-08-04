#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include "Simulation.h"

using namespace sf;

int main()
{
    const float INITIAL_ALIVE_CELL_PERCENTAGE = 0.45f;
    const int CELL_SIZE = 10;
    const int GRID_ROWS = 64;
    const int GRID_COLS = 64;
    const int WINDOW_WIDTH = GRID_COLS * CELL_SIZE;
    const int WINDOW_HEIGHT = GRID_ROWS * CELL_SIZE;


    Simulation sim(GRID_ROWS, GRID_COLS, INITIAL_ALIVE_CELL_PERCENTAGE);
    assert(sim.currentGrid().getRows() == GRID_ROWS);

    for (int i = 0; i < 20; i++)
    {
        sim.checkAllNeighbours();
        sim.updateAllCells();
    }

    sim.scatterSprinkles(100);

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cellular Simulation Test");
    window.setFramerateLimit(15);
    sim.displayGrid(window, CELL_SIZE);

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        sim.moveSprinkles();
        sim.reproduceSprinkles();
        sim.pruneMatureSprinkles();
        sim.displayGrid(window, CELL_SIZE);
    }

    return 0;
}
