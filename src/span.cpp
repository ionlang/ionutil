#include <stdexcept>
#include <ionshared/span.h>

namespace ionshared {
    uint32_t Span::getEndPosition() const noexcept {
        return this->startPosition + this->length;
    }

    bool Span::overlapsWith(Span span) const {
        // TODO: Implement.
        throw std::runtime_error("Not implemented");
    }

    Span Span::createSubSpan(uint32_t startPosition, uint32_t length) const {
        // TODO: Implement.
        throw std::runtime_error("Not implemented");
    }
}
