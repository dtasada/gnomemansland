#include "../include/server.hpp"
#include <cstdlib>
#include <iostream>

using json = nlohmann::json;

struct Troop {
    int id, x, y, health;

    json to_json() const { return json{{"id", id}, {"x", x}, {"y", y}, {"health", health}}; }

    static Troop from_json(const json &j) {
        return {
            .id = j.at("id").get<int>(),
            .x = j.at("x").get<int>(),
            .y = j.at("y").get<int>(),
            .health = j.at("health").get<int>(),
        };
    }
};

int main(int argc, char *argv[]) {
    std::cout << "My Troop" << Troop::from_json(json::parse("{'id': 69, 'x': 2, 'y': 4, 'health': 100}")).to_json().dump()
              << std::endl;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return EXIT_FAILURE;
    }

    Server server(atoi(argv[1]));
    server.listen();
    return EXIT_SUCCESS;
}
