#pragma once

#include <string>

namespace ionshared {
    struct Span {
        uint32_t startPosition = 0;

        uint32_t length = 0;

        [[nodiscard]] uint32_t getEndPosition() const noexcept;

        [[nodiscard]] bool overlapsWith(Span span) const;

        [[nodiscard]] Span createSubSpan(uint32_t startPosition, uint32_t length) const;
    };
}
