#pragma once    
#include <memory>  
#include "Sprinkle.h"  

class Cell
{
private:
    // Data members
    bool wall_present;
    bool future_wall_state;
    bool food_present;
    std::unique_ptr<Sprinkle> sprinkle_ptr;

public:
    // Constructor
    explicit Cell(bool initial_wall_state);

    // Getter methods
    bool hasWall() const;
    bool willBeWall() const;
    bool hasSprinkle() const;
    Sprinkle* getSprinkle();

    // Setter methods
    void setFutureWallState(bool future_state);
    void placeSprinkle(std::unique_ptr<Sprinkle> new_sprinkle);

    // Update method
    void updateCurrentWallState();

    // Sprinkle management
    std::unique_ptr<Sprinkle> removeSprinkle();

    bool hasFood() const;

    void placeFood();

    void removeFood();
};
