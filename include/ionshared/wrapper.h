#pragma once

namespace ionshared {
    template<typename T>
    class Wrapper {
    protected:
        T value;

    public:
        explicit Wrapper(T value) :
            value(value) {
            //
        }

        virtual T& unwrap() {
            return this->value;
        }

        virtual const T& unwrapConst() const {
            return this->value;
        }
    };
}
