#pragma once

#include <string>
#include <ionshared/util.h>
#include <ionshared/container/vector.h>
#include "diagnostic.h"

namespace ionshared {
    /**
     * Helper class to easily build and bootstrap diagnostics.
     */
    class DiagnosticBuilder : public std::enable_shared_from_this<DiagnosticBuilder> {
    private:
        std::optional<Diagnostic> diagnosticBuffer;

        void assertDiagnosticBufferSet() const;

        void setDiagnosticBuffer(std::optional<Diagnostic> diagnosticBuffer) noexcept;

    public:
        const std::shared_ptr<Vector<Diagnostic>> diagnostics;

        explicit DiagnosticBuilder(
            std::shared_ptr<Vector<Diagnostic>> diagnostics =
                std::make_shared<Vector<Diagnostic>>()
        );

        [[nodiscard]] std::optional<Diagnostic> getDiagnosticBuffer() const noexcept;

        void clearDiagnosticBuffer() noexcept;

        [[nodiscard]] std::shared_ptr<DiagnosticBuilder> begin(Diagnostic diagnostic) noexcept;

        [[nodiscard]] std::shared_ptr<DiagnosticBuilder> begin(
            DiagnosticKind type,
            std::string message,
            std::optional<SourceLocation> location = std::nullopt
        ) noexcept;

        [[nodiscard]] std::shared_ptr<DiagnosticBuilder> beginInfo(
            std::string message,
            std::optional<SourceLocation> location = std::nullopt
        ) noexcept;

        [[nodiscard]] std::shared_ptr<DiagnosticBuilder> beginWarning(
            std::string message,
            std::optional<SourceLocation> location = std::nullopt
        ) noexcept;

        [[nodiscard]] std::shared_ptr<DiagnosticBuilder>beginError(
            std::string message,
            std::optional<SourceLocation> location = std::nullopt
        ) noexcept;

        [[nodiscard]] std::shared_ptr<DiagnosticBuilder> beginFatal(
            std::string message,
            std::optional<SourceLocation> location = std::nullopt
        ) noexcept;

        [[nodiscard]] bool internalAssert(bool condition) noexcept;

        [[nodiscard]] std::shared_ptr<DiagnosticBuilder> setMessage(std::string message);

        [[nodiscard]] std::shared_ptr<DiagnosticBuilder> setSourceLocation(
            std::optional<SourceLocation> location
        );

        [[nodiscard]] std::shared_ptr<DiagnosticBuilder> setCode(std::optional<uint32_t> code);

        [[nodiscard]] std::shared_ptr<DiagnosticBuilder> setAdditionalInformation(
            std::optional<std::string> additionalInformation
        );

        [[nodiscard]] std::shared_ptr<DiagnosticBuilder> setExample(
            std::optional<std::string> example
        );

        void finish();

        /**
         * Will attempt to format the currently buffered diagnostic's
         * message with the provided arguments. If the formatting fails,
         * the message will not be changed.
         */
        template<typename ...Args>
        [[nodiscard]] std::shared_ptr<DiagnosticBuilder> formatMessage(Args &&...args) {
            this->assertDiagnosticBufferSet();

            std::optional<std::string> formattedMessage = util::formatStringA(
                this->diagnosticBuffer->message,
                util::convertString(std::forward<Args>(args))...
            );

            if (formattedMessage.has_value()) {
                this->diagnosticBuffer->message = *formattedMessage;
            }

            return this->shared_from_this();
        }

        [[nodiscard]] std::shared_ptr<DiagnosticBuilder> bootstrap(
            Diagnostic diagnostic,
            std::optional<SourceLocation> sourceLocation = std::nullopt
        );
    };
}
