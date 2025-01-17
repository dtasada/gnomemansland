#include "../include/server.hpp"
#include <cstdlib>
#include <iostream>
#include <sqlite_orm/sqlite_orm.h>

struct Troop {
    int id, x, y, health;
};

int main(int argc, char *argv[]) {
    using namespace sqlite_orm;
    auto storage =
        make_storage("server/game.db", make_table("troops", make_column("id", &Troop::id, primary_key().autoincrement()),
                                                  make_column("x", &Troop::x), make_column("y", &Troop::y),
                                                  make_column("health", &Troop::health)));

    storage.sync_schema();
    storage.replace(Troop{42, 10, 20, 10000000});
    storage.replace(Troop{69, 1, 40, -2000});

    for (Troop &t : storage.get_all<Troop>()) {
        std::cout << "Troop ID: " << t.id << ", Position: (" << t.x << ", " << t.y << "), Health: " << t.health
                  << ", Health: " << t.health << std::endl;
    }

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return EXIT_FAILURE;
    }

    Server server(atoi(argv[1]));
    server.listen();
    return EXIT_SUCCESS;
}
