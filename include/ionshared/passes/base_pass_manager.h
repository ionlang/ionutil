#pragma once

#include <concepts>
#include <vector>
#include <queue>
#include <ionshared/helpers.h>
#include <ionshared/base_construct.h>
#include "pass_info.h"

namespace ionshared {
    enum struct PassPriority {
        /**
         * Highest priority. This precedence will be executed first.
         */
        Important,

        /**
         * The default priority.
         */
        Normal,

        Low,

        Lowest
    };

    /**
     * Holds passes which will traverse the construct AST once
     * invoked. Passes can be registered with prerequisites.
     */
    template<typename TPass, typename TConstruct>
//        requires std::derived_from<TPass, BasePass<TConstruct>>
    class BasePassManager {
    public:
        struct Item;

    private:
        Set<PassId> registeredPasses;

    public:
        struct Item {
            std::shared_ptr<TPass> pass;

            PassInfo info;

            PassPriority priority;
        };

        std::vector<Item> passes;

        BasePassManager() noexcept :
            passes(),
            registeredPasses() {
            //
        }

        template<PassLike T>
            requires std::derived_from<T, TPass>
        [[nodiscard]] bool isRegistered() const {
            return this->registeredPasses.contains(&T::passId);
        }

        /**
         * Register a pass without invoking the pass' initialization method.
         * This will skip requirements and invalidations caused by the pass.
         */
        template<PassLike T>
            requires std::derived_from<T, TPass>
        bool registerPassWithoutInit(std::shared_ptr<T> pass, auto priority = PassPriority::Normal) {
            if (this->registeredPasses.contains(&T::passId)) {
                return false;
            }

            this->registeredPasses.add(&T::passId);

            this->passes.push_back(Item{
                pass,
                PassInfo(),
                priority
            });

            return true;
        }

        /**
         * Register a pass if it's requirements are met when the pass'
         * initialization method is invoked.
         */
        template<PassLike T>
            requires std::derived_from<T, TPass>
        bool registerPass(std::shared_ptr<T> pass, auto priority = PassPriority::Normal) {
            auto info = PassInfo();

            pass->initialize(info);

            std::set<PassId> requirements = info.requirements.unwrapConst();

            for (const auto& requirement : requirements) {
                if (!this->registeredPasses.contains(requirement)) {
                    return false;
                }
            }

            // TODO: Handle invalidations.

            return this->registerPassWithoutInit<T>(pass, priority);
        }

        /**
         * Traverse all nodes and visit each one of them, and their
         * child nodes if applicable.
         */
        void run(const Ast<TConstruct>& ast) {
            auto compare = [](Item left, Item right) {
                // TODO: Ensure correct order.
                return left.priority > right.priority;
            };

            std::priority_queue<
                Item,
                std::vector<Item>,
                decltype(compare)
            > runQueue(compare);

            // Push pass manager items onto the queue, thus ordering them.
            for (const auto& item : this->passes) {
                runQueue.push(item);
            }

            /**
             * Loop through the resulting ordered queue and start
             * executing passes.
             */
            while (!runQueue.empty()) {
                Item item = runQueue.top();

                runQueue.pop();

                for (auto& topLevelConstruct : ast) {
                    item.pass->prepare();
                    item.pass->visit(topLevelConstruct);
                    item.pass->finish();
                }
            }
        }
    };
}
