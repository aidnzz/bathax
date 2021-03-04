#pragma once

#include <array>
#include "math.hpp"

template<size_t I>
using padding_t = std::array<std::byte, I>;

namespace lego 
{
    constexpr size_t HERO_COUNT = 2;

    struct alignas(4) fields_t
    {
        const padding_t<0xc0> _;
        float jump_force;
    };

    struct alignas(4) stats_t
    {
        const padding_t<0x24> _;
        fields_t* const fields;
    };

    struct alignas(4) Entity
    {
        Entity* const self;
        const padding_t<0x50> _;
        stats_t* const stats;
        const padding_t<0x4> _1;
        math::vector3f_t position; // 0x5c
        math::vector3f_t velocity; // 0x68
        const padding_t<0xb14> _2;
        size_t* const coins; // 0xb88
        const padding_t<0xa3a> _3;
        int8_t max_health; //0x15C6
        int8_t health; //0x15C7
        const padding_t<0x80> _4;
    };

    using entity_t = Entity;

    static_assert(sizeof(entity_t) == 0x1648, "Entity has an invalid size. Check structures alignment.");
}
