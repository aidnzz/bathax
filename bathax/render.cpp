#include "render.hpp"
#include "modules.hpp"

#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

namespace render 
{
    auto IDrawable::end() const noexcept -> void
    {
        ImGui::End();
    }

    auto initialise(HWND hwnd, const LPDIRECT3DDEVICE9 device) noexcept -> void
    {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableSetMousePos;
        ImGui::StyleColorsDark();
        ImGui_ImplWin32_Init(hwnd); 
        ImGui_ImplDX9_Init(device);
    }

    auto draw_box(const ImVec2& pos, const ImVec2& dimensions, const ImColor& colour) noexcept -> void
    {
        ImGui::GetBackgroundDrawList()->AddRect(pos, ImVec2(pos.x + dimensions.x, pos.y + dimensions.y), colour);
    }

    auto draw_line(const ImVec2& from, const ImVec2& to, const ImColor& color, float thickness) noexcept -> void
    {
        ImGui::GetBackgroundDrawList()->AddLine(from, to, color, thickness);
    }

    auto draw_text(const ImVec2& pos, const ImColor& color, const std::string_view text) noexcept -> void
    {
        ImGui::GetBackgroundDrawList()->AddText(pos, color, text.data());
    }
}
