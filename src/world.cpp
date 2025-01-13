#include "../include/world.hpp"

World::World(int width, int height){
    this->width = width;
    this->height = height;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < height; x++) {
            mapData[y][x] = 3;
        }
    }
}

void World::update() {
    draw();
}

void World::draw() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < height; x++) {
            printf("asd");
        }
    }
}