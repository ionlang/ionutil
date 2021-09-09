#pragma once

#include <ionshared/span.h>

namespace ionshared {
    struct SourceLocation {
        Span lines;

        Span column;
    };
}
