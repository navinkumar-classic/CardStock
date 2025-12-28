/**
* @file GameState.h
 * @brief represents the game state entity
 *
 * Header file containing the game state entity
 *
 * @author Navin Kumar<omnavinyogesh.icc@gmail.com>
 * @date 2025-12-22
 * @version 0.1.0
 * @copyright
 *
 * Change Log:
 * - 2025-12-22: created file ~ Navin Kumar.
 * - 2025-12-22: implementated game state entity that can handle <int, bool, float, string> variables dynamically.
 *               set(), get(), has(), remove(), getAsString(), applyDelta() intialised ~ Navin Kumar.
 * - 2025-12-23: implemented iterator functionality for the gameStateMap using begin(), end() ~ Navin Kumar.
 * - 2025-12-24: added functionality to serialize/deserialize into JSON ~ Navin Kumar.
 */

#pragma once
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

template <typename T> concept varTypeName = std::disjunction_v<std::is_same<T, int>, std::is_same<T, float>, std::is_same<T, bool>, std::is_same<T, std::string>>;
template <typename T> concept numTypeName = std::disjunction_v<std::is_same<T, int>, std::is_same<T, float>>;
using varType = std::variant<int, float, bool, std::string>;

class GameState{
    public:
        GameState() = default;
        ~GameState() = default;

        template <varTypeName T> void set(const std::string& key, T value) {
            gameStateMap[key] = value;
        }

        template <varTypeName T> std::optional<T> get(const std::string& key) const{
            const auto it = gameStateMap.find(key);
            if (it != gameStateMap.end()) {
                if (auto val = std::get_if<T>(&it->second)) {
                    return *val;
                }
            }
            return std::nullopt;
        }

        bool has(const std::string& key) const{
            const auto it = gameStateMap.find(key);
            if (it != gameStateMap.end()){
                return true;
            }
            return false;
        }

        bool remove(const std::string& key) {
            const auto it = gameStateMap.find(key);

            if (it != gameStateMap.end()){
                gameStateMap.erase(it);
                return true;
            }
            return false;
        }

        template <numTypeName T> bool applyDelta(const std::string& key, T delta) {
            if (auto val = get<T>(key)) {
                set(key, *val + delta);
                return true;
            }

            return false;
        }

        template <varTypeName T> std::optional<std::string> getAsString(const std::string& key) {
            auto val = get<T>(key);
            if (!val) {
                return std::nullopt;
            }

            if constexpr (std::is_same_v<T, std::string>) {
                return val.value();
            }
            else if constexpr ( std::is_same_v<T, bool>) {
                return val.value() ? "true" : "false";
            }
            else {
                return std::to_string(val.value());
            }
        }

        auto begin() const { return std::begin(gameStateMap); }
        auto end() const { return std::end(gameStateMap); }

        void initFromJson(const json& j);
        json toJson() const;

    private:
        std::unordered_map<std::string, varType> gameStateMap;

};
