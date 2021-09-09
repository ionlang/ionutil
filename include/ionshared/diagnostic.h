#pragma once

#include <string>
#include <vector>
#include <ionshared/helpers.h>
#include <ionshared/container/stack.h>
#include "source_location.h"

namespace ionshared {
    enum struct DiagnosticKind {
        /**
         * An internal error of the compiler. These errors are meant
         * to be debugged and fixed by the compiler developer(s).
         * Internal compiler errors cannot be recovered from because
         * they are essential.
         */
        InternalError,

        /**
         * An informative message meant to inform the user.
         */
        Info,

        /**
         * A warning which points out to the user that something could
         * be improved.
         */
        Warning,

        /**
         * An error or illegal event, which cannot be tolerated by the
         * compiler.
         */
        Error,

        /**
         * An unrecoverable error which prevents the compiler from continuing
         * doing its job, which may include lexing, parsing, code generation,
         * etc.
         */
        Fatal
    };

    /**
     * Holds valuable information about information messages, warnings,
     * errors, etc. Contains the type of diagnostic, message, source
     * location, and other various informational fields.
     */
    struct Diagnostic {
        DiagnosticKind kind;

        std::string message;

        std::optional<SourceLocation> sourceLocation = std::nullopt;

        /**
         * The unique identifying diagnostic code. Used to uniquely
         * identify certain diagnostics from others.
         */
        std::optional<uint32_t> code = std::nullopt;

        /**
         * An optional example of what happened and why it happened,
         * and possibly a brief explanation of how to fix/address the
         * problem or situation.
         */
        std::optional<std::string> example = std::nullopt;

        /**
         * Any additional information to understand the problem or
         * situation, which may have been omitted from the original
         * message for simplicity.
         */
        std::optional<std::string> additionalInformation;
    };
}
