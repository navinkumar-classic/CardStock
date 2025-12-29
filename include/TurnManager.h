/**
* @file TurnManager.h
 * @brief represents the entity that manages turns in the game
 *
 * Header file containing the entity that manages each turn.
 *
 * @author Vishal R<echelora.@gmail.com>
 * @date 2025-12-25
 * @version 0.1.0
 * @copyright
 *
 */

#pragma once

#include <vector>
#include <cstddef>

// A turn consists of three phases:
//   Start: Prepare the game state for the player to take actions,
//          trigger start of turn effects.
//   Main:  Game is played, logic is processed, engine validates actions,
//   End:   Clean up phase, trigger end of turn effects,
//          next turn is started.
enum class TurnPhase {
    Start,
    Main,
    End
};

class TurnManager {
public:
    TurnManager();

    void init(size_t playerCount);

    [[nodiscard]] size_t getCurrentPlayerIndex() const;
    [[nodiscard]] size_t getTurnNumber() const;
    [[nodiscard]] TurnPhase getPhase() const;

    [[nodiscard]] bool isPlayersTurn(size_t playerIndex) const;

    void nextPhase();
    void goToStartPhase();
    void endTurn();

private:
    size_t currentPlayerIndex_;
    size_t turnNumber_;
    TurnPhase currentPhase_;
    size_t playerCount_;

    void advanceToNextPlayer(int delta);
};
