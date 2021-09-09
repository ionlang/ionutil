#pragma once

#include <map>
#include <string>
#include <optional>
#include <memory>
#include <vector>
#include <functional>

namespace ionshared {
    template<typename T>
    using Ptr = std::shared_ptr<T>;

    template<typename T>
    using ConstPtr = std::shared_ptr<const T>;

    template<typename T>
    using OptPtr = std::optional<std::shared_ptr<T>>;

    template<typename T>
    using Ref = std::reference_wrapper<T>;

    template<typename T>
    using OptRef = std::optional<Ref<T>>;

    /**
     * Alias for a reference vector.
     */
    template<typename T>
    using RefV = std::vector<Ref<T>>;
}
