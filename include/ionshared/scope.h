#pragma once

#include <ionshared/base_construct.h>
#include <ionshared/wrapper.h>
#include <ionshared/helpers.h>

namespace ionshared {
    enum struct ScopeKind {
        Block
    };

    struct Scope : Wrapper<std::shared_ptr<Construct>> {
        const ScopeKind kind;

        Scope(std::shared_ptr<Construct> value, ScopeKind kind);
    };
}
