#include "Utils.h"

// Generates a random weighted boolean value
bool utils::generateRandomWeightedBool(float trueProbability)
{
    static std::random_device randomDevice;  // Initialize a random device
    static std::mt19937 randomEngine(randomDevice());  // Initialize a random engine using the random device
    std::bernoulli_distribution distribution(trueProbability);  // Initialize a Bernoulli distribution with the given true probability
    return distribution(randomEngine);  // Return a random boolean based on the distribution and engine
}

// Return a ColorValue with random RGB values
ColourValue utils::generateRandomColorValue()
{
    static std::random_device randomDevice; 
    static std::mt19937 randomEngine(randomDevice());  
    std::uniform_int_distribution<int> distribution(0, 255); 
    return ColourValue(distribution(randomEngine), distribution(randomEngine), distribution(randomEngine)); 
}