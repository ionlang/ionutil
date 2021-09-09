#pragma once

#include <optional>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>
#include <ionshared/wrapper.h>
#include <ionshared/safe_wrapper.h>
#include <ionshared/helpers.h>
#include "llvm_inst.h"

namespace ionshared {
    class LlvmBlock : public SafeWrapper<llvm::BasicBlock*> {
    private:
        OptPtr<llvm::IRBuilder<>> cachedBuilder;

    public:
        explicit LlvmBlock(llvm::BasicBlock* value) noexcept;

        [[nodiscard]] std::shared_ptr<llvm::IRBuilder<>> getBuilder();

        [[nodiscard]] OptPtr<LlvmInst> findTerminatorInst() const;

        [[nodiscard]] OptPtr<LlvmInst> findInstById(std::string id);
    };
}
