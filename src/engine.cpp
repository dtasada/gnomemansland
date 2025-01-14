#include "../include/engine.hpp"
#include <iostream>
#include <random>

int randint(int a, int b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(a, b);
    return dis(gen);
}
