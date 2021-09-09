#pragma once

#include <vector>
#include <ionshared/symbol_table.h>
#include <ionshared/scoped.h>

namespace ionshared {
    template<typename T>
        // TODO: Type constrains for T?
    struct Context {
        typedef PtrSymbolTable<T> Scope;

        std::vector<Scope> scopes;

        Scope globalScope;

        explicit Context(
            Scope globalScope = util::makePtrSymbolTable<T>(),
            std::vector<Scope> scopes = {}
        ) :
            globalScope(std::move(globalScope)),
            scopes(std::move(scopes)) {
            //
        }

        void appendScope(const Scope& scope) noexcept {
            // Scope is already on the scopes vector.
            if (util::locateInVector(this->scopes, scope) != std::nullopt) {
                return;
            }

            /**
             * Otherwise, push the scope onto the front of the vector.
             * This will allow vector traversal starting from the last
             * added scope, to the first added one.
             */
            this->scopes.insert(this->scopes.begin(), scope);
        }

        template<typename TConstructKind>
        void appendScope(
            const std::shared_ptr<Scoped<T, TConstructKind>>& scopeAnchor
        ) noexcept {
            this->appendScope(scopeAnchor->getSymbolTable());
        }

        /**
         * Removes the lastly added scope from the scopes list.
         * Nothing will happen if the scopes list is empty.
         */
        void popScope() {
            if (!this->scopes.empty()) {
                this->scopes.erase(this->scopes.begin());
            }
        }

        /**
         * Attempt to locate the nearest (starting from most recent
         * scopes) construct by it's id in the scope symbol tables.
         */
        [[nodiscard]] OptPtr<T> findNearest(const std::string& name) {
            /**
             * Scopes vector is already in the correct order because
             * whenever a new scope is pushed, it is added at the beginning
             * instead of the end of the scopes vector, essentially reversing
             * the order from last added to first added.
             */
            for (const auto& scope : this->scopes) {
                if (scope->contains(name)) {
                    return scope->lookup(name);
                }
            }

            // Lastly, check the global scope.
            return this->globalScope->lookup(name);
        }
    };
}
