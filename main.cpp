#include <SFML/Graphics.hpp>
#include <iostream>
#include "Simulation.h"

using namespace sf;

const float INITIAL_WALL_PERCENTAGE = 0.43f;
const int CELL_SIZE = 5;
const int GRID_ROWS = 128;
const int GRID_COLS = 128;
const int SPRINKLE_NUMBER = 1000;
const int FOOD_AMOUNT = 2000;

int main()
{
    Simulation sim(GRID_ROWS, GRID_COLS, INITIAL_WALL_PERCENTAGE);

    RenderWindow window(VideoMode(GRID_ROWS * CELL_SIZE, GRID_COLS * CELL_SIZE), "Sprinkles");
    window.setFramerateLimit(15);

    for (int i = 0; i < 20; i++) {
        sim.prepareAllCells();
        sim.updateAllCells();
    }

    sim.scatterSprinkles(SPRINKLE_NUMBER);
    sim.scatterFood(FOOD_AMOUNT);
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
                sim.scatterFood(FOOD_AMOUNT);
                sim.displayGrid(window, CELL_SIZE);
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {

            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {
                sim = Simulation(GRID_ROWS, GRID_COLS, INITIAL_WALL_PERCENTAGE);
                for (int i = 0; i < 20; i++) {
                    sim.prepareAllCells();
                    sim.updateAllCells();
                }
                sim.scatterSprinkles(SPRINKLE_NUMBER);
                sim.scatterFood(FOOD_AMOUNT);
                sim.displayGrid(window, CELL_SIZE);
            }
        }
        sim.setDestinationForAllSprinkles();
        sim.moveAllSprinkles();
        sim.displayGrid(window, CELL_SIZE);
    }

    return 0;
}
