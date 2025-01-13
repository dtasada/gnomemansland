#include "../include/world.hpp"

World::World(v2 size) : size(size) {
    map_data = std::vector<std::vector<int>>(size.y, std::vector<int>(size.x));

    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            map_data[y][x] = 3;
        }
    }
}

void World::update() { draw(); }

void World::draw() {
    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            printf("asd");
        }
    }
}
