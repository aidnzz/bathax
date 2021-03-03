#pragma once

#include <d3d9.h>
#include <memory>
#include <string_view>

#include "imgui/imgui.h" // ImVec2

namespace render {
    class IScreen
    {
    public:
        virtual auto end() const noexcept -> void = 0;
        virtual auto begin() const noexcept -> bool = 0;
    };

    class IDrawable : public IScreen
    {
    public:
        auto end() const noexcept -> void override;
        virtual auto draw() const noexcept -> void = 0;
    };

    class Menu final : public IDrawable
    {
    public:
        auto draw() const noexcept -> void override;
        auto begin() const noexcept -> bool override;
    };

    class Frame final : public IDrawable
    {
    public:
        auto end() const noexcept -> void override;
        auto draw() const noexcept -> void override;
        auto begin() const noexcept -> bool override;
    };

    template<typename T>
        requires std::is_base_of_v<IScreen, T>
    class screen_manager
    {
    public:
        using pointer = std::add_pointer_t<std::add_const_t<T>>;
        
        screen_manager() noexcept
            : m_screen(T()), m_status(m_screen.begin()) { }

        ~screen_manager() noexcept 
        {
            m_screen.end(); 
        }

        [[nodiscard]] explicit operator bool() const noexcept
        {
            return m_status;
        }

        [[nodiscard]] auto operator->() const noexcept -> pointer
        {
            return &m_screen;
        }

    private:
        T m_screen;
        bool m_status;
    };

    auto initialise(HWND hwnd, const LPDIRECT3DDEVICE9 device) noexcept -> void;
    
    auto draw_box(const ImVec2& pos, const ImVec2& dimensions, const ImColor& colour) noexcept -> void;
    auto draw_line(const ImVec2& from, const ImVec2& to, const ImColor& color, float thickness = 1.0f) noexcept -> void;
    auto draw_text(const ImVec2& pos, const ImColor& colour, const std::string_view text) noexcept -> void;
}