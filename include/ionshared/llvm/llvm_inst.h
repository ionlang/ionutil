#pragma once

#include <llvm/IR/Instruction.h>
#include <ionshared/wrapper.h>
#include <ionshared/safe_wrapper.h>

namespace ionshared {
    struct LlvmInst : SafeWrapper<llvm::Instruction*> {
        explicit LlvmInst(llvm::Instruction* value);

        std::string getId() const;
    };
}
