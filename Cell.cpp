#include "Cell.h"

// Constructor
Cell::Cell(bool initial_wall_state) : wall_present(initial_wall_state), future_wall_state(false), food_present(false) {}

// Getter methods
bool Cell::hasWall() const
{
	return this->wall_present;
}

bool Cell::willBeWall() const
{
	return this->future_wall_state;
}

void Cell::setFutureWallState(bool future_state)
{
	this->future_wall_state = future_state;
}

void Cell::updateCurrentWallState()
{
	this->wall_present = this->future_wall_state;
}

bool Cell::hasSprinkle() const
{
	return this->sprinkle_ptr != nullptr;	// sprinkle_ptr is a unique pointer, so comparing with nullptr is enough to check existence
}

// Get the sprinkle object from this cell
Sprinkle* Cell::getSprinkle() {
	return sprinkle_ptr.get(); 	// Return raw pointer to the sprinkle object, ownership remains with the unique_ptr
}

// Place a new sprinkle in this cell
void Cell::placeSprinkle(std::unique_ptr<Sprinkle> new_sprinkle) {
	this->sprinkle_ptr = std::move(new_sprinkle); 	// Take ownership of the sprinkle pointer passed into the function
}

// Remove the sprinkle from this cell
std::unique_ptr<Sprinkle> Cell::removeSprinkle() {
	return std::move(sprinkle_ptr); // Transfer ownership of sprinkle pointer to caller
}


bool Cell::hasFood() const
{
	return this->food_present;
}

void Cell::placeFood()
{
	this->food_present = true;
}

void Cell::removeFood() {
	this->food_present = false;
}