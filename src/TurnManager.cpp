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

#include <stdexcept>

TurnManager::TurnManager(): currentPlayerIndex_(0), turnNumber_(1),
                            currentPhase_(TurnPhase::Start), playerCount_(0),
                            reverse_(false), skip_(false), restart_(false), skipCount_(0) {}

void TurnManager::init(size_t playerCount) {
    playerCount_ = playerCount;
    currentPlayerIndex_ = 0;
    turnNumber_ = 1;
    currentPhase_ = TurnPhase::Start;
    reverse_ = false;
    skip_ = false;
    restart_ = false;
    skipCount_ = 0;
}

size_t TurnManager::getCurrentPlayerIndex() const {
    return currentPlayerIndex_;
}

size_t TurnManager::getNextIthPlayerIndex(int i) const {
    return offsetIndex(i);
}

size_t TurnManager::getPreviousIthPlayerIndex(int i) const {
    return offsetIndex(-i);
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
            throw std::runtime_error("TurnManager::nextPhase: TurnPhase::End reached");
    }
}

void TurnManager::goToStartPhase() {
    currentPhase_ = TurnPhase::Start;
}

void TurnManager::endTurn() {
    if (restart_) {
        restart_ = false;
        currentPhase_ = TurnPhase::Start;
        return;
    }
    if (skip_) {
        skip_ = false;
        advanceToNextPlayer(skipCount_);
        currentPhase_ = TurnPhase::Start;
        return;
    }
    if (currentPhase_ == TurnPhase::End) {
        advanceToNextPlayer(1);
        currentPhase_ = TurnPhase::Start;
    }
}

void TurnManager::reverseTurn() {
    reverse_ = !reverse_;
}

void TurnManager::restartTurn() {
    restart_ = true;
}

void TurnManager::skipTurn(int skipCount) {
    skip_ = true;
    skipCount_ = skipCount + 1;
}
void TurnManager::advanceToNextPlayer(int delta) {
    currentPlayerIndex_ = offsetIndex(delta);
    turnNumber_++;
}

size_t TurnManager::offsetIndex(int offset) const {
    if (playerCount_ == 0) {
        return 0;
    }
    using index_t = std::ptrdiff_t;

    const auto count = static_cast<index_t>(playerCount_);
    const auto current = static_cast<index_t>(currentPlayerIndex_);
    const index_t dir = reverse_ ? -1 : 1;
    const index_t off = static_cast<index_t>(offset) * dir;

    index_t idx = (current + off) % count;
    if (idx < 0) {
        idx += count;
    }

    return static_cast<size_t>(idx);
}
