#include <iostream>
#include <fstream>

#include "include/Engine.h"
#include "util/Action.h"
#include "util/Event.h"

int main() {
    std::ifstream f("../example/JSON/FullGame/uno.json");
    json j = json::parse(f);

    Engine game(j);
    game.run();

    return 0;
}