#include "Sprinkle.h"
#include <random>

Sprinkle::Sprinkle() {
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