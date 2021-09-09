#pragma once

#include <vector>
#include <ionshared/llvm/llvm_module.h>
#include <ionir/inst.h>
#include <ionir/passes/codegen/llvm_codegen_pass.h>
#include <ionir/lexical/token.h>
#include <ionir/lexical/token_kind.h>
#include <ionir/syntax/parser.h>
#include <ionir/helpers.h>
#include "util.h"

namespace ionshared::test::bootstrap {
    [[nodiscard]] Token token(TokenKind kind = TokenKind::Unknown);

    [[nodiscard]] TokenStream tokenStream(int amountOfItems = 1);

    [[nodiscard]] Parser parser(std::vector<Token> tokens);

    [[nodiscard]] std::shared_ptr<ionshared::LlvmModule> llvmModule(
        const std::string &identifier = "test"
    );

    [[nodiscard]] std::shared_ptr<LlvmCodegenPass> llvmCodegenPass(
        const std::shared_ptr<ionshared::LlvmModule> &module = llvmModule()
    );

    [[nodiscard]] std::shared_ptr<Function> emptyFunction(
        std::vector<std::shared_ptr<Inst>> insts = {}
    );
}
