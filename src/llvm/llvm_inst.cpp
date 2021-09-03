#include <ionshared/llvm/llvm_inst.h>

namespace ionshared {
    LlvmInst::LlvmInst(llvm::Instruction* value) :
        SafeWrapper(value) {
        //
    }

    std::string LlvmInst::getId() const {
        return this->value->getName().str();
    }
}
