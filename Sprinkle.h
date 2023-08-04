#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <set>
#include <random>

#include "grid.h"

class Sprinkle {
private:
    void randomizeColor();

    // Current position
    int x, y;

    // RGB colour
    int red, green, blue;

    // Age
    int age;

    // How many cells away the Sprinkle can see
    int sightRange;

    std::pair<int, int> currentDestination;

    bool travelling;

public:
    Sprinkle(int x, int y, int sightDistance);

    Sprinkle(int x, int y, int red, int green, int blue, int sightDistance);

    sf::Color getColor() const;

    std::pair<int, int> getPosition() const;
    void setPosition(int x, int y);

    void setCurrentDestination(std::pair<int, int> destination);

    std::pair<int, int> move();
    
    void increaseAge();

    int getAge() const;
    
    int getSightRange() const;

    bool isTravelling() const;

    void setTravelling(bool travelParam);
};