#include "Entity.h"
#include <random>

Entity::Entity() {
    randomizeColor();
}

sf::Color Entity::getColor() const {
    return sf::Color(red, green, blue);
}

void Entity::randomizeColor() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 255);

    red = dis(gen);
    green = dis(gen);
    blue = dis(gen);
}