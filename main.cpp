#include <SFML/Graphics.hpp>
#include <iostream>
#include "Automaton.h"

using namespace sf;

int main()
{
    const float INITIAL_ALIVE_CELL_PERCENTAGE = 0.45f;

    const int NUMBER_OF_ITERATIONS = 20; // The number of iterations for each automaton
    const int NUMBER_OF_GRIDS = 10; // The number of different starting grids

    const int CELL_SIZE = 10; // Adjust this value to change the size of the cells

    // Adjust these values to control the number of rows and columns in the grid
    const int DESIRED_GRID_ROWS = 128;
    const int DESIRED_GRID_COLS = 128;

    // Retrieve desktop screen mode
    VideoMode desktopMode = VideoMode::getDesktopMode();

    // Calculate the maximum allowed grid rows and columns based on the screen resolution
    int maxGridRows = desktopMode.height / CELL_SIZE;
    int maxGridCols = desktopMode.width / CELL_SIZE;

    // Choose the minimum between desired and maximum values to ensure it fits the screen
    const int GRID_ROWS = std::min(DESIRED_GRID_ROWS, maxGridRows);
    const int GRID_COLS = std::min(DESIRED_GRID_COLS, maxGridCols);

    const int WINDOW_WIDTH = GRID_COLS * CELL_SIZE;
    const int WINDOW_HEIGHT = GRID_ROWS * CELL_SIZE;

    Automaton automaton(GRID_ROWS, GRID_COLS, INITIAL_ALIVE_CELL_PERCENTAGE);
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cellular Automaton");
    window.setFramerateLimit(20);

    for (int i = 0; i < 20; i++)
    {
        {
            automaton.checkAllNeighbours();
            automaton.updateAllCells();
        }
    }

    automaton.scatterEntities(2000);

    automaton.displayGrid(window, CELL_SIZE);

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

        automaton.checkAllNeighbours();
        automaton.updateAllCells();
        automaton.moveEntities();

        // Draw the automaton to the window
        automaton.displayGrid(window, CELL_SIZE);  // Assume cell size is 20 pixels
    }

    return 0;
}
