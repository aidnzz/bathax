#include "render.hpp"
#include "config.hpp"
#include "modules.hpp"

#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

namespace render 
{
    auto Frame::begin() const noexcept -> bool
    {
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        return true;
    }

    auto Frame::draw() const noexcept -> void
    {
        if (config::menu_enabled)
        {
            if (const auto menu = screen_manager<Menu>())
                menu->draw();
        }

        if (config::esp_enabled)
            modules::esp();
    }

    auto Frame::end() const noexcept -> void
    {
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    }
}
