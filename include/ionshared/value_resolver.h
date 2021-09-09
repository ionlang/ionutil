#pragma once

#include <optional>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Constant.h>
//#include <ionshared/value/integer.h>

namespace ionshared {
    class ValueResolver {
    protected:
        llvm::Module *module;

    public:
        ValueResolver(llvm::Module *module);

        // TODO
//        std::optional<llvm::Constant *> tryResolveInt(IntegerKind kind, long value, bool isSigned = true);
    };
}
