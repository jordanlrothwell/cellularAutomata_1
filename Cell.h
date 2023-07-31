#pragma once
#include "Entity.h"
class Cell
{

private:
	bool currentState;
	bool nextState;
	Entity* entity;


public:
	Cell(bool initialStateParam);

	~Cell();

	const bool isWall();

	const bool getNextState();

	void setNextState(int stateParam);

	void updateState();

	bool hasEntity() const;

	Entity* getEntity() const;

	void setEntity(Entity* newEntity);

	// Remove entity (without deleting it)
	Entity* removeEntity();
};

