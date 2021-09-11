#pragma once

#include <string>
#include <ionshared/string_table.h>
#include <ionshared/iterable.h>

namespace ionshared {
    template<typename T>
    struct BaseToken {
        T kind;

        std::string value;

        uint32_t startPosition;

        uint32_t lineNumber;

        BaseToken(
            T kind,
            std::string value,
            uint32_t startPosition = 0,
            uint32_t lineNumber = 0
        ) :
            kind(kind),
            value(value),
            startPosition(startPosition),
            lineNumber(lineNumber) {
            //
        }

        [[nodiscard]] uint32_t getEndPosition() const noexcept {
            return this->startPosition + this->value.length();
        }

        bool operator==(const BaseToken<T>& other) const {
            return this->value == other.value &&
                this->kind == other.kind &&
                this->startPosition == other.startPosition;
        }

        bool operator!=(const BaseToken<T>& other) const {
            // Simplifying this causes a SIGSEGV (segmentation fault).
            return !(*this == other);
        }
    };

    template<typename T>
    using BaseTokenStream = Iterable<BaseToken<T>>;
}
