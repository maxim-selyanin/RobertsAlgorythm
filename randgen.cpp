#include "randgen.h"

RandomGenerator::RandomGenerator(float min, float max)
    : gen(std::random_device()())
    , dist(min, max)
{}

float RandomGenerator::operator()() {
    return dist(gen);
}
