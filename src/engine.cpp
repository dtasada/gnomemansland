#include "../include/engine.hpp"
#include <iostream>
#include <random>

int64_t randint(int64_t a, int64_t b) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int64_t> dis(a, b);
    return dis(gen);
}

float rand01() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}
