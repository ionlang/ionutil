#pragma once

#include "generator.h"

namespace ionshared {
    /**
     * A generator which returns no items during each
     * iteration.
     */
    typedef Generator<void> LooseGenerator;
}
