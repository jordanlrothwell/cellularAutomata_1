#include <SFML/Graphics.hpp>
#include <iostream>
#include "Simulation.h"

using namespace sf;

const float INITIAL_ALIVE_CELL_PERCENTAGE = 0.43f;
const int CELL_SIZE = 10;
const int GRID_ROWS = 64;
const int GRID_COLS = 64;
const int WINDOW_WIDTH = GRID_COLS * CELL_SIZE * 2;
const int WINDOW_HEIGHT = GRID_ROWS * CELL_SIZE;
const int SPRINKLE_NUMBER = 200;


Simulation* startNewSim(int sprinkles) {
    Simulation* sim = new Simulation(GRID_ROWS, GRID_COLS, INITIAL_ALIVE_CELL_PERCENTAGE, WINDOW_WIDTH);
    for (int i = 0; i < 20; i++)
    {
        sim->checkAllNeighbours();
        sim->updateAllCells();
    }

    sim->scatterSprinkles(sprinkles);
    return sim;
}

int main()
{
    Simulation* sim = startNewSim(SPRINKLE_NUMBER);

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sprinkles");
    window.setFramerateLimit(15);

    View simulationView(FloatRect(0, 0, GRID_COLS * CELL_SIZE, WINDOW_HEIGHT));
    simulationView.setViewport(FloatRect(0, 0, 0.5f, 1.0f));

    View statisticsView(FloatRect(0, 0, GRID_COLS * CELL_SIZE, WINDOW_HEIGHT));
    statisticsView.setViewport(FloatRect(0.5f, 0, 0.5f, 1.0f));

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
                delete sim; // Delete the old simulation to prevent memory leaks
                sim = startNewSim(SPRINKLE_NUMBER);
            }
        }

        sim->chooseSprinkleDestinations();
        sim->moveSprinkles();
        sim->reproduceSprinkles();
        sim->pruneMatureSprinkles();

        window.setView(simulationView);
        sim->displayGrid(window, CELL_SIZE);
    }

    delete sim; // Delete the simulation after the main loop

    return 0;
}

