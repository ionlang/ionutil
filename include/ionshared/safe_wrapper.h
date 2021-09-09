#pragma once

#include "wrapper.h"

namespace ionshared {
    /**
     * A wrapper derivative class which verifies that its value is
     * not nullptr on the constructor. If nullptr for the value is
     * provided, an exception will be thrown.
     */
    template<typename T>
    class SafeWrapper : public Wrapper<T> {
    public:
        explicit SafeWrapper(T value) :
            Wrapper<T>(value) {
            if (value == nullptr) {
                // TODO: Can you catch
                throw std::runtime_error("Cannot construct LLVM entity wrapper with a null value");
            }
        }
    };
}
