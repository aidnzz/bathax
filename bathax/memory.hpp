#pragma once

#include <cinttypes>
#include <type_traits>

namespace memory {
    template<typename T>
    [[nodiscard]] auto read(const uintptr_t addr) -> std::add_lvalue_reference_t<T>
    {
        return *reinterpret_cast<std::add_pointer_t<T>>(addr);
    }
}