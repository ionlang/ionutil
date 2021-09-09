#pragma once

#include <memory>
#include <queue>
#include <functional>
#include <ionshared/base_construct.h>
#include <ionshared/symbol_table.h>
#include <ionshared/util.h>

namespace ionshared {
    template<typename T>
    using TraversalCallback = std::function<bool(T)>;

    // TODO: Implement concepts to ensure T is or derives of Construct.
    template<typename TConstruct, typename TConstructKind>
        // TODO: Used partially in projects (incomplete type).
//        requires std::derived_from<TConstruct, BaseConstruct<TConstruct, TConstructKind>>
    struct Scoped {
        typedef Scoped<TConstruct, TConstructKind> Self;

        PtrSymbolTable<TConstruct> symbolTable;

        OptPtr<Self> parentScope;

        explicit Scoped(
            PtrSymbolTable<TConstruct> symbolTable =
                util::makePtrSymbolTable<TConstruct>(),

            OptPtr<Self> parent = std::nullopt
        ) :
            symbolTable(symbolTable),
            parentScope(parent) {
            //
        }

        [[nodiscard]] bool hasParentScope() const noexcept {
            return util::hasValue(this->parentScope);
        }

        // TODO: Hotfix by passing in self shared pointer.
        /**
         * Traverses parent scopes starting from the nearest one, and
         * including itself.
         */
        void traverseScopes(
            std::shared_ptr<Self> self,
            TraversalCallback<std::shared_ptr<Self>> callback
        ) {
            std::queue<std::shared_ptr<Self>> queue = {};

            queue.push(self);

            while (!queue.empty()) {
                std::shared_ptr<Self> scope = queue.front();

                queue.pop();

                if (!callback(scope)) {
                    break;
                }
                else if (scope->hasParentScope()) {
                    queue.push(*scope->parentScope);
                }
            }
        }

        [[nodiscard]] std::optional<TConstruct> findNearestSymbol(std::string name) {
            std::optional<TConstruct> result = std::nullopt;

            this->traverseScopes([&, this](std::shared_ptr<Self> scope) -> bool {
                OptPtr<TConstruct> symbol = scope->getSymbolTable()->lookup(name);
                bool hasValue = util::hasValue(symbol);

                if (hasValue) {
                    result = symbol;
                }

                return hasValue;
            });

            return result;
        }

        [[nodiscard]] std::optional<TConstruct> findNearestSymbol(
            std::string name,
            TConstructKind constructKind
        ) {
            std::optional<TConstruct> result = std::nullopt;

            this->traverseScopes([&, this](std::shared_ptr<Self> scope) -> bool {
                OptPtr<TConstruct> symbol = scope->getSymbolTable()->lookup(name);

                if (util::hasValue(symbol)
                    && symbol->get()->constructKind == constructKind) {
                    result = symbol;

                    return false;
                }

                return true;
            });

            return result;
        }
    };
}
