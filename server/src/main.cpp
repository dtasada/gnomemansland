#include "../include/server.hpp"

#include <cstdlib>
#include <iostream>
#include <ostream>

struct Troop {
    int id, x, y, health;

    std::string dump() const {
        return json{
            {    "id",     id},
            {     "x",      x},
            {     "y",      y},
            {"health", health}
        }.dump(4);
    }

    static Troop from_json(const json &j) {
        return {
            .id     = j.at("id").get<int>(),
            .x      = j.at("x").get<int>(),
            .y      = j.at("y").get<int>(),
            .health = j.at("health").get<int>(),
        };
    }

    friend std::ostream &operator<<(std::ostream &os, const Troop &troop) {
        os << "Troop(id=" << troop.id << ", x=" << troop.x << ", y=" << troop.y
           << ", health=" << troop.health << ")";
        return os;
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return EXIT_FAILURE;
    }

    Server server(atoi(argv[1]));
    server.listen();

    std::cout << "My Troop: " << server.database.dump(4) << std::endl;

    return EXIT_SUCCESS;
}
