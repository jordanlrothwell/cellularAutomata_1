#pragma once
class Cell
{

private:
	bool currentState;
	bool nextState;

public:
	Cell(bool initialStateParam);

	const bool isWall();

	const bool getNextState();

	void setNextState(int stateParam);

	void updateState();
};

