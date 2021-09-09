#pragma once

#include <concepts>
#include "base_construct.h"

namespace ionshared {
    template<typename TRootConstruct, typename TConstructKind, typename TConstruct>
        requires std::derived_from<TRootConstruct, BaseConstruct<TRootConstruct, TConstructKind>>
            && std::derived_from<TConstruct, TRootConstruct>
    class ConstructBuilder {
    private:
        typedef ConstructBuilder<TRootConstruct, TConstructKind, TConstruct> Self;

        typedef BaseConstruct<TRootConstruct, TConstructKind> Construct;

        std::optional<std::shared_ptr<TConstruct>> construct;

        std::shared_ptr<TConstruct> requireConstruct() {
            if (!ionshared::util::hasValue(this->construct)) {
                throw std::runtime_error("Construct is unset");
            }

            return *this->construct;
        }

    public:
        ConstructBuilder() noexcept :
            construct() {
            //
        }

        template<typename ...Args>
        Self& begin(Args&&... args) {
            this->construct = std::make_shared<TConstruct>(args...);

            return this;
        }

        Self& begin() {
            this->construct = std::make_shared<TConstruct>();

            return this;
        }

        Self& setParent(std::shared_ptr<Construct> parent) {
            this->requireConstruct()->parent = parent;

            return this;
        }

        /**
         * Finish building the construct. Ensures that the parent
         * has been previously set.
         */
        std::shared_ptr<TConstruct> make() {
            std::shared_ptr<TConstruct> construct = this->requireConstruct();

            if (!ionshared::util::hasValue(construct->parent)) {
                throw std::runtime_error("Parent is unset");
            }

            return construct;
        }
    };
}
