#pragma once

#include <optional>
#include <ionshared/util.h>
#include "map.h"

namespace ionshared {
    template<typename TFirst, typename TSecond>
    struct BiMap {
        Map<TFirst, TSecond> firstMap;

        Map<TSecond, TFirst> secondMap;

        explicit BiMap(std::map<TFirst, TSecond> value = {}) noexcept :
            firstMap(Map<TFirst, TSecond>(value)),
            secondMap(Map<TSecond, TFirst>(util::flipMap<TFirst, TSecond>(value))) {
            //
        }

        explicit BiMap(std::initializer_list<std::pair<const TFirst, TSecond>> list) noexcept :
            BiMap(std::map<TFirst, TSecond>(list)) {
            //
        }

        bool insert(TFirst first, TSecond second, bool overwrite = false) {
            return this->firstMap.set(first, second, overwrite)
                && this->secondMap.set(second, first, overwrite);
        }

        bool insert(TSecond second, TFirst first, bool overwrite = false) {
            return this->insert(first, second, overwrite);
        }

        [[nodiscard]] std::optional<TSecond> lookup(TFirst first) {
            return this->firstMap.lookup(first);
        }

        [[nodiscard]] std::optional<TFirst> lookup(TSecond second) {
            return this->secondMap.lookup(second);
        }

        [[nodiscard]] bool contains(TFirst first) const {
            return this->firstMap.contains(first);
        }

        [[nodiscard]] bool contains(TSecond second) const {
            return this->secondMap.contains(second);
        }

        /**
         * Attempt to merge the local entries with another map's
         * entries. Returns std::nullopt if duplicate keys or values
         * were encountered.
         */
        std::optional<BiMap<TFirst, TSecond>> merge(BiMap<TFirst, TSecond> other) const {
            BiMap<TFirst, TSecond> newMap = BiMap<TFirst, TSecond>();

            // TODO: Check for existing keys in both maps.

            for (const auto [key, value] : this->firstMap.unwrapConst()) {
                if (!newMap.insert(key, value)) {
                    return std::nullopt;
                }
            }

            for (const auto [key, value] : other.firstMap.unwrapConst()) {
                if (!newMap.insert(key, value)) {
                    return std::nullopt;
                }
            }

            return newMap;
        }
    };
}
