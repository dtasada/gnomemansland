#include "../include/engine.hpp"
#include <iostream>
#include <random>


// structs
/* v3 Color::WATER_LOW = v3(0, 0, 50);
v3 Color::WATER_HIGH = v3(30, 110, 140);
v3 Color::SAND_LOW = v3(237, 206, 178);
v3 Color::SAND_HIGH = v3(255, 245, 193);
v3 Color::GRASS_LOW = v3(0, 140, 90);
v3 Color::GRASS_HIGH = v3(0, 120, 80);
v3 Color::MOUNTAIN_LOW = v3(80, 80, 80);
v3 Color::MOUNTAIN_HIGH = v3(120, 120, 120); */

// functions
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

v3 lerp_color(v3 c1, v3 c2, float m) {
    return c1 + v3(m, m, m) * (c2 - c1);
}
