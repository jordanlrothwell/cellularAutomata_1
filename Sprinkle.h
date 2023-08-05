#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <set>
#include <random>
#include "Utils.h"

class Sprinkle {
private:
    // Data members
    Coords current_position;
    ColourValue colour;
    int age;
    int sight_range;
    OptionalCoords current_destination;

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
    OptionalCoords move();
    void increaseAge();
};
