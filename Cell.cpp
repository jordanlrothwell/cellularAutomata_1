#include "Cell.h"

Cell::Cell(bool initialStateParam)
{
	this->isWall = initialStateParam;
	this->willBeWall = false;
	this->sprinkle = nullptr;
}

const bool Cell::getIsWall()
{
	return this->isWall;
}

const bool Cell::getWillBeWall()
{
	return this->willBeWall;
}

void Cell::setFutureState(bool inputBool)
{
	this->willBeWall = inputBool;
}

void Cell::updateCurrentState()
{
	this->isWall = this->willBeWall;
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