#include "../include/engine.hpp"
#include <random>
#include <iostream>

int randint(int a, int b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(a, b);
    return dis(gen);
}
