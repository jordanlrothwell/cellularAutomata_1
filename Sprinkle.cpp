#include "Sprinkle.h"

Sprinkle::Sprinkle(int x, int y, int sight_range)
    : current_position{ x, y }, colour(utils::generateRandomColorValue()), age(0), sight_range(sight_range), current_destination(std::nullopt) {}

Sprinkle::Sprinkle(int x, int y, ColourValue colour, int sight_range)
    : current_position{ x, y }, colour(colour), age(0), sight_range(sight_range), current_destination(std::nullopt) {}

ColourValue Sprinkle::getColour() const {
    return this->colour;
}

Coords Sprinkle::getPosition() const {
    return this->current_position;
}

void Sprinkle::setPosition(int new_x, int new_y) {
    this->current_position = { new_x, new_y };
}

OptionalCoords Sprinkle::getCurrentDestination() const {
    return this->current_destination;
}

void Sprinkle::setDestination(OptionalCoords new_destination) {
    this->current_destination = new_destination;
}

OptionalCoords Sprinkle::move() {
   
    Coords next_position = this->current_position;
    OptionalCoords optional_destination = this->current_destination;
    if (optional_destination) {
        Coords actual_destination = optional_destination.value();
        if (this->current_position.x < actual_destination.x) {
            next_position.x += 1;
        }
        else if (this->current_position.x > actual_destination.x) {
            next_position.x -= 1;
        }

        if (this->current_position.y < actual_destination.y) {
            next_position.y += 1;
        }
        else if (this->current_position.y > actual_destination.y) {
            next_position.y -= 1;
        }

        return next_position;
    }
    return std::nullopt;
}


void Sprinkle::increaseAge() {
    this->age++;
}

int Sprinkle::getAge() const
{
    return this->age;
}

int Sprinkle::getSightRange() const {
    return this->sight_range;
}

bool Sprinkle::isTravelling() const {
    return static_cast<bool>(this->current_destination);
}
