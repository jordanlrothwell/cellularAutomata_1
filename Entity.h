#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity();

    sf::Color getColor() const;

private:
    void randomizeColor();

    int red;
    int green;
    int blue;
};