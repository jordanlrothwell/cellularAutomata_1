#include "Cell.h"

Cell::Cell(bool initialStateParam)
{
	this->hasWall = initialStateParam;
	this->willHaveWall = false;
	this->sprinkle = nullptr;
}

const bool Cell::isWall()
{
	return this->hasWall;
}

const bool Cell::getWillBeWall()
{
	return this->willHaveWall;
}

void Cell::setFutureState(bool inputBool)
{
	this->willHaveWall = inputBool;
}

void Cell::updateCurrentState()
{
	this->hasWall = this->willHaveWall;
}

bool Cell::hasSprinkle() const
{
	return this->sprinkle != nullptr;
}

Sprinkle* Cell::getSprinkle() const {
	return sprinkle.get();
}

void Cell::setSprinkle(std::unique_ptr<Sprinkle> sprinkle) {
	this->sprinkle = std::move(sprinkle);
}

std::unique_ptr<Sprinkle> Cell::removeSprinkle() {
	return std::move(sprinkle);
}