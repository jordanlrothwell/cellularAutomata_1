#pragma once
#include <SFML/Graphics.hpp>

class Sprinkle {
public:
    Sprinkle(int x, int y);

    sf::Color getColor() const;

    std::pair<int, int> getPosition() const;
    void setPosition(int x, int y);

    void move();

private:
    void randomizeColor();

    int x, y;  // Position of the Sprinkle
    int red, green, blue;  // Color of the Sprinkle
};