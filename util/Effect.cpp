
#include "Effect.h"

void Effect::gameOver(GameState& gameState) {
    gameState.set<bool>("isRunning", false);
}