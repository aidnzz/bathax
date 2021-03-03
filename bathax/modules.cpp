#include <span>
#include <ranges>
#include <functional>

#include "lego.hpp"
#include "memory.hpp"
#include "render.hpp"
#include "modules.hpp"

auto modules::esp() noexcept -> void
{
    // Using this as a struct replacement. Might be undefined behavior due to undefined ordering of elements
    using list_t = std::pair<const size_t, const lego::entity_t** const>;
    
    if (const auto& [count, begin] = memory::read<list_t>(lego::offsets::entity_count); begin)
    {
        const auto list = std::span{*begin, count};
        const auto is_alive = std::mem_fn(&lego::Entity::health);

        for (const auto& e : list | std::views::drop(2) | std::views::filter(is_alive))
            continue;
    }
}