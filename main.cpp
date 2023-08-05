#include <SFML/Graphics.hpp>
#include <iostream>
#include "Simulation.h"

using namespace sf;

const float INITIAL_WALL_PERCENTAGE = 0.47f;
const int CELL_SIZE = 10;
const int GRID_ROWS = 128;
const int GRID_COLS = 128;
const int SPRINKLE_NUMBER = 1500;

int main()
{
    Simulation sim(GRID_ROWS, GRID_COLS, INITIAL_WALL_PERCENTAGE);

    RenderWindow window(VideoMode(GRID_ROWS * CELL_SIZE, GRID_COLS * CELL_SIZE), "Sprinkles");
    window.setFramerateLimit(15);

    // Display the initial state of the grid before entering the main loop.
    sim.displayGrid(window, CELL_SIZE);

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                window.close();
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
            {
                sim.prepareAllCells();
                sim.updateAllCells();
                sim.displayGrid(window, CELL_SIZE);
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                sim.scatterSprinkles(SPRINKLE_NUMBER);
                sim.displayGrid(window, CELL_SIZE);  // Display the updated state of the grid after scattering sprinkles.
            }
        }
    }

    return 0;
}
