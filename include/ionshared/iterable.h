#pragma once

#include <exception>
#include <vector>
#include <optional>
#include <ionshared/util.h>
#include "generator.h"

namespace ionshared {
    template<typename T>
    class Iterable : public Generator<T> {
    protected:
        /**
         * Signifies the current item position of the list.
         */
        size_t index;

        std::vector<T> items;

        [[nodiscard]] size_t resolveNextIndex() {
            return this->resolveIndex(this->index + 1);
        }

        size_t nextIndex() {
            // Resolve and set the next index safely.
            this->index = this->resolveNextIndex();

            // Return the current index.
            return this->index;
        }

        [[nodiscard]] size_t resolveIndex(size_t index) {
            size_t size = this->items.size();

            // Provided index is within bounds.
            if (size > index) {
                return index;
            }

            // Index is out-of-bounds, return the last valid index.
            return size - 1;
        }

        size_t updateIndex(size_t index) {
            this->index = this->resolveIndex(index);

            return this->index;
        }

    public:
        explicit Iterable(std::vector<T> items) :
            index(0),
            items() {
            this->items = items;

            // Ensure items array contains at least one item.
            if (this->items.size() == 0) {
                throw std::runtime_error("Items array cannot be empty");
            }

            // Set the initial index to the first item.
            this->begin();
        }

        /**
         * Whether the current index points to the last item
         * on the Stream. A Stream always contains at least one item.
         */
        virtual bool hasNext() const override {
            return this->index < this->items.size() - 1;
        }

        virtual std::optional<T> tryNext() override {
            // Resolve the next index safely.
            size_t nextIndex = this->nextIndex();

            // Retrieve and return the item.
            return this->items[nextIndex];
        }

        [[nodiscard]] virtual T next() {
            std::optional<T> item = this->tryNext();

            if (!item.has_value()) {
                throw std::runtime_error("No more items in iterable");
            }

            return *item;
        }

        void skip(uint32_t amount = 1) {
            if (amount < 1) {
                throw std::out_of_range("Amount must greater than zero");
            }

            this->updateIndex(this->index + amount);
        }

        /**
         * Access the next item (if any) without altering the
         * index.
         */
        [[nodiscard]] virtual std::optional<T> peek() {
            // No more items to process.
            if (!this->hasNext()) {
                return std::nullopt;
            }

            // TODO: operator[] creates a new entry if none exist.
            // Return the next item without altering the index.
            return this->items[this->resolveNextIndex()];
        }

        /**
         * Reset the index to its initial value (0).
         */
        virtual void begin() override {
            this->index = 0;
        }

        /**
         * Retrieve the current item on the Stream by
         * the current index.
         */
        [[nodiscard]] T get() const noexcept {
            // Return the item at the current index.
            return this->items[this->index];
        }

        /**
         * Retrieve the index of the Stream. Indicates the location
         * of the current item.
         */
        [[nodiscard]] size_t getIndex() const noexcept {
            return this->index;
        }

        /**
         * Returns the total amount of items.
         */
        [[nodiscard]] size_t getSize() const noexcept {
            return this->items.size();
        }

        std::optional<uint32_t> locate(T item) const {
            return util::locateInVector(this->items, item);
        }

        [[nodiscard]] std::vector<T> slice(uint32_t start, uint32_t length) {
            return util::sliceVector<T>(this, start, length);
        }
    };
}
