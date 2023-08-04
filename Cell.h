#pragma once
#include "Sprinkle.h"
class Cell
{

private:
	bool hasWall;
	bool willHaveWall;

	std::unique_ptr<Sprinkle> sprinkle;

public:
	Cell(bool initialStateParam);

	const bool isWall();

	const bool getWillBeWall();

	void setFutureState(bool inputBool);
	void updateCurrentState();

	bool hasSprinkle() const;
	Sprinkle* getSprinkle() const;
	void setSprinkle(std::unique_ptr<Sprinkle> sprinkle);

	// This function removes the sprinkle from the cell and returns it wrapped in a unique_ptr.
	// If the returned unique_ptr is not stored anywhere, the sprinkle will be automatically deleted from memory.
	std::unique_ptr<Sprinkle> removeSprinkle();
};

