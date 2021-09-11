#pragma once

#include <ionshared/string_table.h>

namespace ionshared {
    // TODO: Why have a struct for just a single field? Because of middle point conversions? Ex. dyn_cast<Named>? Where is it even used?
    struct Named {
        StringIndex name;
    };
}
