#include "Sprinkle.h"

Sprinkle::Sprinkle(int x, int y, int sight_range)
    : current_position{ x, y }, colour(utils::generateRandomColorValue()), age(0), sight_range(sight_range), travelling(false), current_destination(std::nullopt) {}

Sprinkle::Sprinkle(int x, int y, ColourValue colour, int sight_range)
    : current_position{ x, y }, colour(colour), age(0), sight_range(sight_range), travelling(false), current_destination(std::nullopt) {}

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

    if (!this->current_destination.has_value()) {
        this->travelling = false;
    }
    else {
        this->travelling = true;
    }
}


std::queue<Coords> Sprinkle::getCoordsInRangeClosestToFurthest() const {

    std::queue<Coords> coordsClosestToFurthest;

    for (int current_distance = 1; current_distance <= sight_range; current_distance++) { 
        for (int i = 1; i < (2 * current_distance); i++) {
            coordsClosestToFurthest.push({ (current_position.x - current_distance) + i, current_position.y + current_distance});
            coordsClosestToFurthest.push({ (current_position.x + current_distance), (current_position.y + current_distance) - i });
            coordsClosestToFurthest.push({ (current_position.x + current_distance) - i, (current_position.y - current_distance) });
            coordsClosestToFurthest.push({ (current_position.x - current_distance), (current_position.y - current_distance) + i });
        }
    }

    return coordsClosestToFurthest;
}
/*
    - This function operates around the outer ring of a square with dimensions of 2n+1 x 2n+1, where n = current_size.
    - The process begins from the top left-hand corner of the current ring - illustrated as (1) below.
    - For the next 2n cells, the cells are added to a queue while moving right.
    - This approach is consistently applied for each corner of the ring for (2), (3), (4), with the exception of the current starting position.
    - This ensures that when the sprinkle sends coordinates within its range to the simulation, they are arranged by proximity in a queue.

    Legend:
    -------
    ◻ : Empty cell
    X  : Starting point for the current iteration
    ◼ : Cell being processed
    --►: Movement to the right
    ◄--: Movement to the left
    ▼  : Movement downwards
    ▲  : Movement upwards
    *  : Reference point (center)
    ________________________________________________________________________________________________________________________________________________

                                                                    current_size = 1
    ________________________________________________________________________________________________________________________________________________

    1)    ◻     ◻     ◻     ◻     ◻     2)     ◻     ◻     ◻     ◻     ◻     3)     ◻     ◻     ◻     ◻     ◻     4)     ◻     ◻     ◻     ◻     ◻


          ◻     X --► ◼ --► ◼     ◻            ◻     ◻     ◻     X     ◻             ◻     ◻     ◻     ◻     ◻           ◻     ◼     ◻     ◻     ◻
                                                                 |                                                             ▲
                                                                 ▼                                                             |
          ◻     ◻     *     ◻     ◻            ◻     ◻     *     ◼     ◻             ◻     ◻     *     ◻     ◻           ◻     ◼     *     ◻     ◻
                                                                 |                                                             ▲
                                                                 ▼                                                             |
          ◻     ◻     ◻     ◻     ◻            ◻     ◻     ◻     ◼     ◻             ◻     ◼ ◄-- ◼ ◄-- X     ◻           ◻     X     ◻     ◻     ◻


          ◻     ◻     ◻     ◻     ◻            ◻     ◻     ◻     ◻     ◻             ◻     ◻     ◻     ◻     ◻           ◻     ◻     ◻     ◻     ◻

     ________________________________________________________________________________________________________________________________________________

                                                                    current_size = 2
     ________________________________________________________________________________________________________________________________________________

     1)   X --► ◼ --► ◼ --► ◼ --► ◼        2)  ◻     ◻     ◻     ◻     X        3)    ◻     ◻     ◻     ◻     ◻        4)  ◼     ◻     ◻     ◻     ◻
                                                                       |                                                   ▲
                                                                       ▼                                                   |
          ◻     ◻     ◻     ◻     ◻            ◻     ◻     ◻     ◻     ◼              ◻     ◻     ◻     ◻     ◻            ◼     ◻     ◻     ◻     ◻
                                                                       |                                                   ▲
                                                                       ▼                                                   |
          ◻     ◻     *     ◻     ◻            ◻     ◻     *     ◻     ◼              ◻     ◻     *     ◻     ◻            ◼     ◻     *     ◻     ◻
                                                                       |                                                   ▲
                                                                       ▼                                                   |
          ◻     ◻     ◻     ◻     ◻            ◻     ◻     ◻     ◻     ◼              ◻     ◻     ◻     ◻     ◻            ◼     ◻     ◻     ◻     ◻
                                                                       |                                                   ▲
                                                                       ▼                                                   |
          ◻     ◻     ◻     ◻     ◻            ◻     ◻     ◻     ◻     ◼              ◼ ◄-- ◼ ◄-- ◼ ◄-- ◼ ◄-- X            X     ◻     ◻     ◻     ◻

     ________________________________________________________________________________________________________________________________________________

                                                          ...up to current_size = sight_distance
     ________________________________________________________________________________________________________________________________________________
*/

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
    return this->travelling;
}

Coords Sprinkle::getNextMove() {
    if (!this->current_destination.has_value()) { // handle the case where there's no destination
        return {};
    }
    int dest_x = this->current_destination.value().x;
    int dest_y = this->current_destination.value().y;
    std::queue<Coords> path_to_destination = utils::bresenhamLine(this->current_position.x, this->current_position.y, dest_x, dest_y);

    path_to_destination.pop(); // remove the current position
    if (path_to_destination.empty()) {
        // If the queue is empty after popping, it means the sprinkle is right next to its destination.
        return { dest_x, dest_y };
    }
    return path_to_destination.front();
}

bool Sprinkle::reachedDestination() {
    if (!this->current_destination.has_value()) {
        return false; // If there's no destination, it can't be reached
    }
    return (this->current_destination.value().x == this->current_position.x && this->current_destination.value().y == this->current_position.y);
}
