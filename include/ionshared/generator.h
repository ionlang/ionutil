#pragma once

#include <optional>

namespace ionshared {
    /**
     * A generic generator which may return an
     * item after each iteration. However, it is not
     * guaranteed to do so.
     */
    template<typename T>
    struct Generator {
        virtual ~Generator() = default;

        virtual bool hasNext() const = 0;

        virtual std::optional<T> tryNext() = 0;

        virtual void begin() = 0;
    };
}
