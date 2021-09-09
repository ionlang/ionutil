#pragma once

#include <utility>
#include <vector>
#include <ionshared/util.h>
#include <ionshared/wrapper.h>

namespace ionshared {
    template<typename T>
    struct Vector : Wrapper<std::vector<T>> {
        explicit Vector(std::initializer_list<T> list = {}) noexcept :
            Wrapper<std::vector<T>>(list) {
            //
        }

        T operator[](size_t index) {
            if (!this->value.empty() && this->value.size() > index) {
                return this->value[index];
            }

            throw std::out_of_range("Index was out of bounds");
        }

        void add(T item) {
            this->value.push_back(item);
        }

        // TODO: Missing remove function (single index, and range overloads).

        bool contains(T item) {
            return util::vectorContains(this->value, item);
        }

        [[nodiscard]] size_t getSize() const noexcept {
            return this->value.size();
        }

        [[nodiscard]] bool isEmpty() const noexcept {
            return this->value.empty();
        }
    };
}
