#pragma once

#include <ionshared/util.h>

namespace ionshared {
    template<typename T>
    class WithParent {
    public:
        std::optional<std::shared_ptr<T>> parent;

        WithParent() :
            parent(std::nullopt) {
            //
        }

        std::shared_ptr<T> forceGetParent() const {
            if (!ionshared::util::hasValue(this->parent)) {
                throw std::runtime_error("Required parent is unset");
            }

            return *this->parent;
        }
    };
}
