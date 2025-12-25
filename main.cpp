
#include <iostream>

#include "include/Card.h"
#include "include/CardZone.h"
#include "include/Engine.h"
#include "include/GameState.h"
#include "include/nlohmann/json.hpp"

#include <fstream>

int main() {
    Engine game;

    game.run();

    /*
    GameState g;
    g.set<float>("val", 5);
    g.applyDelta<float>("val", 10.1);
    std::cout << g.getAsString<float>("val").value_or("null") << std::endl;
    g.remove("val");
    std::cout << g.has("val");
    g.set<std::string>("std", "hello");
    std::cout << g.get<std::string>("std").value_or("null");
    */

    std::ifstream f("../example/JSON/CardZone/CardZone_1.json");

    json czj = json::parse(f);
    CardZone cz(czj);

    cz.shuffle();

    std::cout << cz.at(0).toJson().dump(4) << std::endl;

    return 0;
}
