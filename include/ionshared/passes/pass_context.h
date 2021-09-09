#pragma once

#include <ionshared/diagnostic.h>
#include <ionshared/diagnostic_builder.h>

namespace ionshared {
    struct PassContext {
        const std::shared_ptr<Vector<Diagnostic>> diagnostics;

        const std::shared_ptr<DiagnosticBuilder> diagnosticBuilder;

        explicit PassContext(
            std::shared_ptr<Vector<Diagnostic>> diagnostics =
                std::make_shared<Vector<Diagnostic>>()
        ) noexcept;
    };
}
