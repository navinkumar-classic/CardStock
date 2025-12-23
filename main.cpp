
#include <iostream>

#include "include/Card.h"
#include "include/CardZone.h"
#include "include/Engine.h"
#include "include/GameState.h"
#include "include/nlohmann/json.hpp"

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

    nlohmann::json j;
    j["x"] = 678;
    j["y"] = true;
    j["z"] = "temp_str";
    j["tags"] = {"hehe", "hj"};

    Card c1(j);

    std::cout << c1.toJson().dump(4) << std::endl;

    j["x"] = 9999;

    Card c2(j);

    CardZone cz(true);

    cz.pushFront(std::move(c1));
    cz.pushBack(std::move(c2));

    std::cout << cz.peekFront().toJson().dump(4);

    return 0;
}
