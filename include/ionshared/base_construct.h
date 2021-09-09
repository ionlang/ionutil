#pragma once

#include <queue>
#include <concepts>
#include <stdexcept>
#include <memory>
#include <ionshared/helpers.h>
#include <ionshared/passes/base_pass.h>

namespace ionshared {
    template<typename T>
    using Ast = std::vector<std::shared_ptr<T>>;

    template<typename T>
    using TraversalCallback = std::function<bool(T)>;

    template<typename TConstruct, typename TConstructKind>
    class BaseConstruct :
        public std::enable_shared_from_this<BaseConstruct<TConstruct, TConstructKind>> {
    private:
        typedef BaseConstruct<TConstruct, TConstructKind> Self;

    public:
        const TConstructKind constructKind;

        std::optional<ionshared::SourceLocation> sourceLocation;

        explicit BaseConstruct(
            TConstructKind kind,
            std::optional<ionshared::SourceLocation> sourceLocation = std::nullopt
        ) noexcept :
            constructKind(kind),
            sourceLocation(sourceLocation) {
            //
        }

//        virtual void accept(TPass visitor) = 0;

        [[nodiscard]] virtual bool equals(std::shared_ptr<Self> other) {
            return other == this->shared_from_this();
        }

        [[nodiscard]] virtual Ast<TConstruct> getChildrenNodes() {
            // By default, construct contains no children.
            return {};
        }

        /**
         * Determine whether this construct has no parent and is therefore
         * considered a root node.
         */
        [[nodiscard]] bool isRootNode() noexcept {
            return util::hasValue(this->parent);
        }

        /**
         * Determine whether this construct has no children and is therefore
         * considered a leaf node.
         */
        [[nodiscard]] bool isLeafNode() {
            return this->getChildrenNodes().empty();
        }

        // TODO
        void traverseChildren(TraversalCallback<std::shared_ptr<Self>> callback) {
            std::queue<std::shared_ptr<Self>> childrenQueue = {};
            Ast<Self> primeChildren = this->getChildrenNodes();

            // Begin with this construct's children nodes.
            for (const auto child : primeChildren) {
                childrenQueue.push(primeChildren);
            }

            while (!childrenQueue.empty()) {
                std::shared_ptr<Self> child = childrenQueue.front();
                Ast<Self> children = child->getChildrenNodes();

                childrenQueue.pop();

                for (const auto& childOfChild : children) {
                    childrenQueue.push(childOfChild);
                }

                // Invoke the callback, and do not continue if it returns false.
                if (!callback(child)) {
                    return;
                }
            }
        }

//        void traverseParents(TraversalCallback<std::shared_ptr<Self>> callback) {
//            if (!util::hasValue(this->parent)) {
//                return;
//            }
//
//            std::queue<std::shared_ptr<Self>> parentQueue{};
//
//            parentQueue.push(*this->parent);
//
//            while (!parentQueue.empty()) {
//                std::shared_ptr<Self> parent = parentQueue.front();
//
//                parentQueue.pop();
//
//                if (!callback(parent)) {
//                    return;
//                }
//                else if (util::hasValue(parent->parent)) {
//                    parentQueue.push(*parent->parent);
//                }
//            }
//        }

//        [[nodiscard]] std::shared_ptr<Self> fetchRoot() {
//            if (!util::hasValue(this->parent)) {
//                return this->shared_from_this();
//            }
//
//            std::queue<std::shared_ptr<Self>> parentQueue{};
//
//            parentQueue.push(*this->parent);
//
//            while (!parentQueue.empty()) {
//                std::shared_ptr<Self> parent = parentQueue.front();
//
//                parentQueue.pop();
//
//                if (!util::hasValue(parent->parent)) {
//                    return parent;
//                }
//
//                parentQueue.push(*parent->parent);
//            }
//        }

        [[nodiscard]] std::shared_ptr<Self> getBarePtr() {
            return this->shared_from_this();
        }

        [[nodiscard]] std::shared_ptr<TConstruct> getPtr() {
            return this->nativeCast();
        }

        /**
         * Used to cast pointers to related types, for example casting
         * void* to the appropriate type.
         */
        template<typename TLike>
        [[nodiscard]] std::shared_ptr<TLike> staticCast() {
            std::shared_ptr<TLike> result = std::static_pointer_cast<TLike>(
                this->shared_from_this()
            );

            if (result == nullptr) {
                throw std::runtime_error("Static pointer cast failed");
            }

            return result;
        }

        /**
         * Used to convert pointers and references at runtime.
         * Should be generally used for casting a pointer or reference
         * up or down an inheritance chain (inheritance hierarchy).
         */
        template<class TLike>
        [[nodiscard]] std::shared_ptr<TLike> dynamicCast() {
            std::shared_ptr<TLike> result =
                std::dynamic_pointer_cast<TLike>(this->shared_from_this());

            if (result == nullptr) {
                throw std::runtime_error("Dynamic pointer cast failed");
            }

            return result;
        }

        [[nodiscard]] std::shared_ptr<TConstruct> nativeCast() {
            return this->dynamicCast<TConstruct>();
        }
    };

    template<typename TDerived, typename TConstruct, typename TConstructKind>
    concept BaseConstructLike =
        std::derived_from<TDerived, BaseConstruct<TConstruct, TConstructKind>>;
}
