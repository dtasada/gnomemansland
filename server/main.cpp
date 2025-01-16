#include "../include/server.hpp"
#include <cstdlib>
#include <iostream>
#include <sqlite3.h>
#include <vector>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return EXIT_FAILURE;
    }

    Server server(atoi(argv[1]));
    server.listen();
    return EXIT_SUCCESS;
}
