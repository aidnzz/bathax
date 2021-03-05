#pragma once

#include <cstddef>
#include "entity.hpp"

namespace lego 
{
    namespace offsets 
    {
        // Array of two hero entity object pointers. This array is 8 bytes in size containing pointers to the entity objects and may contain null pointers.
        // When hero is swapped the pointers will swap
        constexpr uintptr_t heroes = 0x00ab2960;
        // Pointer to d3d9 device
        constexpr uintptr_t device = 0x009cf8d8;
        // Level path of current level
        constexpr uintptr_t level_path = 0x00ab29E8;
        // Entity count
        constexpr uintptr_t entity_count = 0x0ab2648;
        // Entity list start pointer
        constexpr uintptr_t entity_list = 0x0ab264c;
        // Camera object pointer
        constexpr uintptr_t camera = 0;
    }
}
