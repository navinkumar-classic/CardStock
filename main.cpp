
#include <fstream>
#include "include/Engine.h"

int main() {
    std::ifstream f("../example/JSON/FullGame/uno.json");
    json j = json::parse(f);

    Engine game(j);
    game.run();

    return 0;
}