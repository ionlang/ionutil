#pragma once

#include <string>

namespace ionshared {
    class NameMangler {
    public:
        static std::string internal(std::string id);
    };
}
