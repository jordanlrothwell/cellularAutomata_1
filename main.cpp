#include <SFML/Graphics.hpp>
#include <iostream>
#include "Simulation.h"

using namespace sf;

int main()
{
    const float INITIAL_ALIVE_CELL_PERCENTAGE = 0.45f;

    const int NUMBER_OF_ITERATIONS = 20;

    const int CELL_SIZE = 1; 

    const int DESIRED_GRID_ROWS = 64;
    const int DESIRED_GRID_COLS = 64;

    VideoMode desktopMode = VideoMode::getDesktopMode();

    int maxGridRows = desktopMode.height / CELL_SIZE;
    int maxGridCols = desktopMode.width / CELL_SIZE;

    const int GRID_ROWS = std::min(maxGridRows, maxGridCols);
    const int GRID_COLS = GRID_ROWS;

    const int WINDOW_WIDTH = GRID_COLS * CELL_SIZE;
    const int WINDOW_HEIGHT = GRID_ROWS * CELL_SIZE;

    Simulation Simulation(GRID_ROWS, GRID_COLS, INITIAL_ALIVE_CELL_PERCENTAGE);
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cellular Simulation");
    window.setFramerateLimit(20);

    for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
    {
            Simulation.checkAllNeighbours();
            Simulation.updateAllCells();
    }

    Simulation.displayGrid(window, CELL_SIZE);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            }
        }
        // Draw the Simulation to the window

    }

    return 0;
}
