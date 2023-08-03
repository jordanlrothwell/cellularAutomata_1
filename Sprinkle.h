#pragma once
#include <SFML/Graphics.hpp>

class Sprinkle {
public:
    Sprinkle();

    sf::Color getColor() const;

private:
    void randomizeColor();

    int red;
    int green;
    int blue;
};