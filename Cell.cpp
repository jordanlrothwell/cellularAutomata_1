#include "Cell.h"

Cell::Cell(bool initialStateParam)
{
	this->currentState = initialStateParam;
	this->nextState = false;
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
