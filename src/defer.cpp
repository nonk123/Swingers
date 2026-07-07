#include "defer.hpp"

Defer::Defer(const std::function<void()>& functor) : functor(functor) {}

Defer::~Defer() {
    functor();
}
