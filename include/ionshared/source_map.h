#pragma once

#include <ionshared/container/map.h>
#include "source_location.h"

namespace ionshared {
    template<typename T>
    class SourceMap {
    private:
        Map<T, SourceLocation> constructToSourceLocationMap;

        Map<SourceLocation, T> sourceLocationToConstructMap;

    public:
        SourceMap() noexcept :
            constructToSourceLocationMap(),
            sourceLocationToConstructMap() {
            //
        }

        [[nodiscard]] Map<T, SourceLocation> getConstructMap() const noexcept {
            return this->constructToSourceLocationMap;
        }

        [[nodiscard]] Map<SourceLocation, T> getSourceLocationMap() const noexcept {
            return this->sourceLocationToConstructMap;
        }

        [[nodiscard]] bool contains(T construct) const {
            return this->constructToSourceLocationMap.contains(construct);
        }

        [[nodiscard]] bool contains(SourceLocation sourceLocation) const {
            return this->sourceLocationToConstructMap.contains(sourceLocation);
        }

        bool set(T construct, SourceLocation sourceLocation, bool overwrite = true) {
            return this->constructToSourceLocationMap.set(construct, sourceLocation, overwrite);
        }

        bool set(SourceLocation sourceLocation, T construct, bool overwrite = false) {
            return this->sourceLocationToConstructMap.set(sourceLocation, construct, overwrite);
        }

        [[nodiscard]] std::optional<SourceLocation> lookup(T construct) {
            return this->constructToSourceLocationMap.lookup(construct);
        }

        [[nodiscard]] std::optional<T> lookup(SourceLocation sourceLocation) {
            return this->sourceLocationToConstructMap.lookup(sourceLocation);
        }
    };
}
