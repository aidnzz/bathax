#include "lego.hpp"

#include "render.hpp"
#include "config.hpp"
#include "memory.hpp"

namespace render 
{
    auto Menu::begin() const noexcept -> bool
    {
        return ImGui::Begin("Lego mod: by aidn", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings);
    }

    auto Menu::draw() const noexcept -> void
    {
        ImGui::Checkbox("Enable ESP", &config::esp_enabled);
        ImGui::Separator();
        
        if (const auto hero = memory::read<lego::entity_t* const>(lego::offsets::heroes))
        {
            int value = hero->max_health;
            ImGui::SliderInt("Player max health", &value, 8i8, 127i8);
            hero->max_health = value;

            value = hero->health;
            ImGui::SliderInt("Player health", &value, 8i8, 127i8);
            hero->health = value;

            ImGui::SliderFloat("Player jump force", &hero->stats->fields->jump_force, 1.9f, 7.0f);
            ImGui::SliderInt("Player coins", reinterpret_cast<int*>(hero->coins), 0, 20000000);
        }
        else
            ImGui::Text("No heroes available. Please load a game to use the mod");
    }
}
