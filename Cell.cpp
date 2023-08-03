#include "Cell.h"

Cell::Cell(bool initialStateParam)
{
	this->isWall = initialStateParam;
	this->willBeWall = false;
	this->sprinkle = nullptr;
}

Cell::~Cell() {
	delete sprinkle;
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

Sprinkle* Cell::getSprinkle() const
{
	return this->sprinkle;
}

void Cell::setSprinkle(Sprinkle* newSprinkle)
{
	this->sprinkle = newSprinkle;
}

Sprinkle* Cell::removeSprinkle() {
	Sprinkle* e = sprinkle;
	sprinkle = nullptr;
	return e;
}