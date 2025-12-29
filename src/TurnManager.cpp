/**
* @file TurnManager.cpp
 * @brief represents the entity that manages turns in the game
 *
 * Implementation of the entity that manages each turn.
 *
 * @author Vishal R<echelora.@gmail.com>
 * @date 2025-12-25
 * @version 0.1.0
 * @copyright
 *
 */

#include "../include/TurnManager.h"

TurnManager::TurnManager()
    : currentPlayerIndex_(0),
      turnNumber_(1),
      currentPhase_(TurnPhase::Start),
      playerCount_(0) {}

void TurnManager::init(size_t playerCount) {
    playerCount_ = playerCount;
    currentPlayerIndex_ = 0;
    turnNumber_ = 1;
    currentPhase_ = TurnPhase::Start;
}

size_t TurnManager::getCurrentPlayerIndex() const {
    return currentPlayerIndex_;
}

size_t TurnManager::getTurnNumber() const {
    return turnNumber_;
}

TurnPhase TurnManager::getPhase() const {
    return currentPhase_;
}

bool TurnManager::isPlayersTurn(size_t playerIndex) const {
    return playerIndex == currentPlayerIndex_;
}

void TurnManager::nextPhase() {
    switch (currentPhase_) {
        case TurnPhase::Start:
            currentPhase_ = TurnPhase::Main;
            break;
        case TurnPhase::Main:
            currentPhase_ = TurnPhase::End;
            break;
        case TurnPhase::End:
            endTurn();
            break;
    }
}

void TurnManager::goToStartPhase() {
    currentPhase_ = TurnPhase::Start;
}

void TurnManager::endTurn() {
    if (currentPhase_ == TurnPhase::End) {
        advanceToNextPlayer(1);
        currentPhase_ = TurnPhase::Start;
    }
}

void TurnManager::advanceToNextPlayer(int delta) {
    currentPlayerIndex_ = (currentPlayerIndex_ + delta) % playerCount_;
    turnNumber_++;
}
