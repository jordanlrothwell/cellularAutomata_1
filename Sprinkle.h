#pragma once
#include <SFML/Graphics.hpp>

class Sprinkle {
public:
    Sprinkle(int x, int y);

    Sprinkle(int x, int y, int red, int green, int blue);

    sf::Color getColor() const;

    std::pair<int, int> getPosition() const;
    void setPosition(int x, int y);

    std::pair<int, int> move();
    
    void increaseAge();

    int getAge() const;

private:
    void randomizeColor();

    int x, y;
    int red, green, blue;

    int age;
};