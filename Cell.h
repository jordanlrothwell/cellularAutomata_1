#pragma once
#include "Sprinkle.h"
class Cell
{

private:
	bool isWall;
	bool willBeWall;
	std::unique_ptr<Sprinkle> sprinkle;

public:
	Cell(bool initialStateParam);

	const bool getIsWall();

	const bool getWillBeWall();

	void setFutureState(bool inputBool);
	void updateCurrentState();

	bool hasSprinkle() const;
	Sprinkle* getSprinkle() const;
	void setSprinkle(std::unique_ptr<Sprinkle> sprinkle);
	std::unique_ptr<Sprinkle> removeSprinkle();
};

