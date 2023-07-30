#include <SFML/Graphics.hpp>
#include <iostream>
#include "Automaton.h"

using namespace sf;

int main()
{
    const float INITIAL_ALIVE_CELL_PERCENTAGE = 0.47f;

    const int NUMBER_OF_ITERATIONS = 20; // The number of iterations for each automaton
    const int NUMBER_OF_GRIDS = 10; // The number of different starting grids

    const int CELL_SIZE = 5; // Adjust this value to change the size of the cells

    // Adjust these values to control the number of rows and columns in the grid
    const int DESIRED_GRID_ROWS = 200;
    const int DESIRED_GRID_COLS = 200;

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
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Num1)
                {
                    // Run simulations for a range of percentages of initially alive cells
                    for (float percentage = INITIAL_ALIVE_CELL_PERCENTAGE; percentage <= INITIAL_ALIVE_CELL_PERCENTAGE + 0.1f; percentage += 0.01f)
                    {
                        float totalWallPercentage = 0.0f; // Keep track of the total wall percentage

                        // For each grid...
                        for (int gridNumber = 0; gridNumber < NUMBER_OF_GRIDS; gridNumber++)
                        {
                            // Create a new automaton with the specified grid size and percentage of initially alive cells
                            automaton = Automaton(GRID_ROWS, GRID_COLS, percentage);

                            // Run the automaton for the specified number of iterations
                            for (int iteration = 0; iteration < NUMBER_OF_ITERATIONS; iteration++)
                            {
                                automaton.checkAllNeighbours();
                                automaton.updateAllCells();
                            }

                            // Get the wall percentage and add it to the total
                            float wallPercentage = automaton.currentGrid().getCurrentWallPercentage();
                            totalWallPercentage += wallPercentage;

                            // Output the wall percentage
                            std::cout << "Grid #" << (gridNumber + 1)
                                << ", Initial life percentage: " << percentage * 100
                                << "%, Current % of walls: " << wallPercentage
                                << "\n";
                        }

                        // Calculate and output the average wall percentage
                        float averageWallPercentage = totalWallPercentage / NUMBER_OF_GRIDS;
                        std::cout << "Average % of walls for initial life percentage of " << percentage * 100
                            << "% across all grids: " << averageWallPercentage << "\n";
                    }
                }
                break;
            case Event::MouseButtonPressed:
                if (event.mouseButton.button == Mouse::Left)
                {
                    automaton.checkAllNeighbours();
                    automaton.updateAllCells();
                    automaton.displayGrid(window, CELL_SIZE);
                    std::cout << "Current % of walls: " << automaton.currentGrid().getCurrentWallPercentage() << "\n";
                }
                else if (event.mouseButton.button == Mouse::Right)
                {
                    automaton = Automaton(GRID_ROWS, GRID_COLS, INITIAL_ALIVE_CELL_PERCENTAGE);
                    automaton.displayGrid(window, CELL_SIZE);
                }
                break;
            }
        }
    }

    return 0;
}
