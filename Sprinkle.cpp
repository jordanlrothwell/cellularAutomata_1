#include "Sprinkle.h"

Sprinkle::Sprinkle(int x, int y, int sightRange) : x(x), y(y), sightRange(sightRange) {
    randomizeColor();
    this->age = 0;
    this->travelling = false;
}

Sprinkle::Sprinkle(int x, int y, int red, int green, int blue, int sightRange)
    : x(x), y(y), red(red), green(green), blue(blue), sightRange(sightRange) {
    this->age = 0;
    this->travelling = false;
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

void Sprinkle::setCurrentDestination(std::pair<int, int> destination) {
    this->currentDestination = destination;
}

std::pair<int, int> Sprinkle::move() {
    
    if (this->getPosition() == this->currentDestination) {
        this->travelling = false;
    }

    int newX = x;
    int newY = y;

    std::pair<int, int> destination = this->currentDestination;

    if (destination.first > x) {
        newX += 1;
    }
    else if (destination.first < x) {
        newX -= 1;
    }

    if (destination.second > y) {
        newY += 1;
    }
    else if (destination.second < y) {
        newY -= 1;
    }

    return { newX, newY };
}


void Sprinkle::increaseAge() {
    this->age++;
}

int Sprinkle::getAge() const
{
    return this->age;
}

int Sprinkle::getSightRange() const {
    return this->sightRange;
}

bool Sprinkle::isTravelling() const {
    return this->travelling;
}

void Sprinkle::setTravelling(bool travelParam) {
    this->travelling = travelParam;
}