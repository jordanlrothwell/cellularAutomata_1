#include "Cell.h"

Cell::Cell(bool initialStateParam)
{
	this->currentState = initialStateParam;
	this->nextState = false;
	this->entity = nullptr;
}

Cell::~Cell() {
	delete entity;
}

const bool Cell::isWall()
{
	return this->currentState;
}

const bool Cell::getNextState()
{
	return this->nextState;
}

void Cell::setNextState(int stateParam)
{
	this->nextState = stateParam;
}

void Cell::updateState()
{
	this->currentState = nextState;
}

bool Cell::hasEntity() const
{
	return this->entity != nullptr;
}

Entity* Cell::getEntity() const
{
	return this->entity;
}

void Cell::setEntity(Entity* newEntity)
{
	this->entity = newEntity;
}

Entity* Cell::removeEntity() {
	Entity* e = entity;
	entity = nullptr;
	return e;
}