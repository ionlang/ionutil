#pragma once

#include <set>
#include <ionshared/wrapper.h>

namespace ionshared {
    template<typename T>
    struct Set : Wrapper<std::set<T>> {
        explicit Set(std::set<T> value = {}) noexcept :
            Wrapper<std::set<T>>(value) {
            //
        }

        explicit Set(std::initializer_list<T> list) noexcept :
            Set(std::set<T>(list)) {
            //
        }

        bool add(T item) {
            return this->value.insert(item).second;
        }

        bool remove(T item) {
            if (this->contains(item)) {
                this->value.erase(item);
            }

            // TODO: Redundant check?
            return this->contains(item);
        }

        [[nodiscard]] bool contains(T item) const {
            return this->value.find(item) != this->value.end();
        }

        [[nodiscard]] size_t getSize() const {
            return this->value.size();
        }

        void clear() {
            this->value.clear();
        }
    };
};
