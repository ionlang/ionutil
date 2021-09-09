#pragma once

#include <string>
#include <llvm/IR/Module.h>
#include <ionshared/wrapper.h>
#include "llvm_context.h"

namespace ionshared {
    class LlvmModule : public Wrapper<llvm::Module*> {
    private:
        LlvmContext* context;

    public:
        LlvmModule(llvm::Module* module, LlvmContext* context);

        explicit LlvmModule(llvm::Module* module);

        ~LlvmModule();

        [[nodiscard]] std::string getId() const;

        void setId(std::string id);

        [[nodiscard]] LlvmContext* getContext() const;

        [[nodiscard]] std::string makeIr() const;

        /**
         * Get LLVM Bitcode from the module. Please note that LLVM
         * Bitcode is a binary representation of LLVM IR, and not object
         * code.
         */
        [[nodiscard]] std::string makeBitcode();

        void printIr();

        void printIrToLlvmErrs() const;
    };

    typedef std::vector<LlvmModule> LlvmProgram;

    typedef std::vector<llvm::Module*> LlvmNativeProgram;

    /**
     * String representing emitted LLVM IR code.
     */
    typedef std::string LlvmIrString;
}
