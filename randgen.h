#pragma once
#include <random>


class RandomGenerator {
    std::mt19937 gen;
    std::uniform_real_distribution<float> dist;

public:
    RandomGenerator(float min, float max);

    float operator()();
};
