#include "../include/engine.hpp"
#include <iostream>
#include <random>

int randint(int a, int b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(a, b);
    return dis(gen);
}

int rand01() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0.0, 1.0);
    return dis(gen);
}
