#pragma once

#include <type_traits>
#include <exception>
#include <stdexcept>
#include <optional>
#include <stack>
#include <ionshared/wrapper.h>

namespace ionshared {
    template<typename T>
    struct Stack : Wrapper<std::stack<T>> {
        explicit Stack(std::stack<T> value = {}) noexcept :
            Wrapper<std::stack<T>>(value) {
            //
        }

        explicit Stack(std::initializer_list<T> list) noexcept :
            Stack(std::stack<T>(list)) {
            //
        }

        ~Stack() {
            // TODO: Is there need clear an std::shared_ptr stack be?
            this->clear();
        }

        void push(T item) {
            this->value.push(item);
        }

        // TODO: Is this being returned as reference or not?
        std::optional<T> tryGetTopItem() {
            if (this->value.empty()) {
                return std::nullopt;
            }

            return this->value.top();
        }

        /**
         * Forcefully get the top item in the stack. Will throw
         * a runtime exception if the stack currently contains no
         * items.
         */
        T forceGetTopItem() {
            std::optional<T> result = this->tryGetTopItem();

            if (!result.has_value()) {
                throw std::runtime_error("No items in the stack");
            }

            return *result;
        }

        // TODO: getBottomItem().

        std::optional<T> tryPop() {
            std::optional<T> result = this->tryGetTopItem();

            // TODO: Review. What if result == nullptr?
            if (result.has_value()) {
                this->value.pop();
            }

            return result;
        }

        /**
         * Forcefully retrieve the top item on the stack, pop it off
         * the stack, and return it. Will throw a runtime exception if
         * the stack does not contain more items.
         */
        T forcePop() {
            std::optional<T> result = this->tryPop();

            if (!result.has_value()) {
                throw std::out_of_range("No more items in stack to pop");
            }

            return *result;
        }

        T popOr(T alternative) {
            std::optional<T> existingItem = this->tryPop();

            if (existingItem.has_value()) {
                return existingItem;
            }

            return alternative;
        }

        [[nodiscard]] bool isEmpty() const {
            return this->value.empty();
        }

        void clear() {
            while (!this->isEmpty()) {
                std::optional<T> item = this->tryPop();

                if (item.has_value() && std::is_pointer<T>::value) {
                    item.reset();
                }
            }
        }

        [[nodiscard]] size_t getSize() const {
            return this->value.size();
        }
    };
}
