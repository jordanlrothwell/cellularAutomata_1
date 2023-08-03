#pragma once
#include "Sprinkle.h"
class Cell
{

private:
	bool isWall;
	bool willBeWall;
	Sprinkle* sprinkle;

public:
	Cell(bool initialStateParam);

	~Cell();

	const bool getIsWall();

	const bool getWillBeWall();

	void setFutureState(bool inputBool);

	void updateCurrentState();

	bool hasSprinkle() const;

	Sprinkle* getSprinkle() const;

	void setSprinkle(Sprinkle* newSprinkle);

	Sprinkle* removeSprinkle();
};

