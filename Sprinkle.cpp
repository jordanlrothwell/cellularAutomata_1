#include "Sprinkle.h"
#include <random>

Sprinkle::Sprinkle(int x, int y) : x(x), y(y) {
    randomizeColor();
    this->age = 0;
}

Sprinkle::Sprinkle(int x, int y, int red, int green, int blue)
    : x(x), y(y), red(red), green(green), blue(blue) {
    this->age = 0;
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

std::pair<int, int> Sprinkle::move() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(-1, 1);

    int newX = x;
    int newY = y;

    if (dis(gen) < 0) {
        newX += dis(gen);
    }
    else {
        newY += dis(gen);
    }

    return { newX, newY };
}

void Sprinkle::increaseAge() {
    this->age++;
}

int Sprinkle::getAge() const {
    return this->age;
}
