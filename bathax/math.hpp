#pragma once

#include <cmath>
#include <array>
#include <cassert>

namespace math 
{
    template<typename T>
        requires std::is_arithmetic_v<T>
    struct Vector3
    {
        constexpr Vector3(const T x, const T y, const T z) noexcept
            : x(x), y(y), z(z) {}

        [[nodiscard("Length is an expensive function")]] constexpr auto length() const noexcept -> T
        {
            return std::hypot(x, y, z);
        }

        T x, y, z;
    };

    using vector3f_t = Vector3<float>;

    template<typename T, size_t R, size_t C>
        requires std::is_arithmetic_v<T>
    using matrix_t = std::array<std::array<T, R>, C>;

    using matrix4x4f_t = matrix_t<float, 4, 4>;
}
