#include "Sprinkle.h"
#include <random>

Sprinkle::Sprinkle(int x, int y) : x(x), y(y) {
    randomizeColor();
}
sf::Color Sprinkle::getColor() const {
    return sf::Color(red, green, blue);
}

void Sprinkle::randomizeColor() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 255);

    red = dis(gen);
    green = dis(gen);
    blue = dis(gen);
}

std::pair<int, int> Sprinkle::getPosition() const {
    return { x, y };
}

void Sprinkle::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Sprinkle::move() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(-1, 1);

    int moveX = dis(gen);
    int moveY = dis(gen);

    x += moveX;
    y += moveY;
}
