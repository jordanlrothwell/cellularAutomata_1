#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <set>
#include <random>
#include <iostream>
#include "Utils.h"
    
class Sprinkle {
private:
    // Data members
    int age;
    ColourValue colour;

    int sight_range;

    Coords current_position;
    OptionalCoords current_destination;
    bool travelling;

public:
    // Constructors
    Sprinkle(int x, int y, int sight_range);
    Sprinkle(int x, int y, ColourValue colour, int sight_range);

    // Getter methods
    ColourValue getColour() const;
    Coords getPosition() const;
    OptionalCoords getCurrentDestination() const;
    int getAge() const;
    int getSightRange() const;
    bool isTravelling() const;

    // Setter methods
    void setPosition(int x, int y);

    void setDestination(OptionalCoords destination);

    // Sprinkle actions
    void increaseAge();

    std::queue<Coords> getCoordsInRangeClosestToFurthest() const;

    Coords getNextMove();

    bool reachedDestination();
};
