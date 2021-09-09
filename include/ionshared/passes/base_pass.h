#pragma once

#include <ionshared/helpers.h>
#include "pass_info.h"
#include "pass_context.h"

#define IONSHARED_PASS_ID static constexpr char passId = 0

namespace ionshared {
    // TODO: Circular.
//    template<typename T, typename TPass>
//    concept ConstructLike = requires(T t, TPass &visitor) {
//        { t.accept(visitor) } -> std::same_as<void>;
//    };

    template<typename T>
    struct BasePass {
        const std::shared_ptr<PassContext> context;

        explicit BasePass(std::shared_ptr<PassContext> context) :
            context(context) {
            //
        }

        virtual void visit(std::shared_ptr<T> node) = 0;

        /**
         * Initialize the pass and register it's constraints. Returns
         * whether the pass was successfully initialized and may be registered
         * by the pass manager or not.
         */
        virtual bool initialize(PassInfo& info) {
            return true;
        }

        /**
         * Invoked when the pass is about to process the AST.
         */
        virtual void prepare() {
            //
        }

        /**
         * Invoked when the pass has traversed the entire AST.
         */
        virtual void finish() {
            //
        }
    };
}
