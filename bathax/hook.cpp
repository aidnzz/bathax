#include <mutex>

#include "lego.hpp"
#include "hook.hpp"
#include "config.hpp"
#include "memory.hpp"

#include "imgui/imgui_impl_win32.h" // ImGui_ImplWin32_WndProcHandler

using present_t = auto(__stdcall*)(LPDIRECT3DDEVICE9 device, LPCRECT src, LPCRECT dst, HWND window, const RGNDATA* region) noexcept -> HRESULT;

static WNDPROC s_wndproc;
static present_t s_present;

const static auto s_window = FindWindowW(L"TTalesWindow", nullptr);

extern [[nodiscard]] IMGUI_IMPL_API auto ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept -> LRESULT;

static auto swap_present() noexcept -> void
{
    if (const auto device_ptr = *reinterpret_cast<void****>(lego::offsets::device))
    {
        DWORD protection;
        auto& fn = memory::read<present_t>(reinterpret_cast<uintptr_t>(*device_ptr) + 0x44);

        if (VirtualProtect(&fn, sizeof present_t, PAGE_READWRITE, &protection))
        {
            std::swap(fn, s_present);
            VirtualProtect(&fn, sizeof present_t, protection, &protection);
        }
    }
}

auto hook::initialise() noexcept -> void
{
    s_present = [](const LPDIRECT3DDEVICE9 device, LPCRECT src, LPCRECT dst, HWND window, const RGNDATA* region) noexcept -> HRESULT
    {
        static std::once_flag flag;
        std::call_once(flag, [device]() { render::initialise(s_window, device); });

        // Drawing goes here
        if (const auto frame = render::screen_manager<render::Frame>())
            frame->draw();

        return s_present(device, src, dst, window, region);
    };

    const WNDPROC proc = [](const HWND hwnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) noexcept -> LRESULT
    {
        static std::once_flag flag;
        std::call_once(flag, swap_present);

        if (msg == WM_KEYDOWN and wParam == VK_F1)
            config::menu_enabled = not config::menu_enabled;

        if (config::menu_enabled)
        {
            if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
                return true;
        }

        return CallWindowProcA(s_wndproc, hwnd, msg, wParam, lParam);
    };

    if (s_window)
        s_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(s_window, GWLP_WNDPROC, reinterpret_cast<uintptr_t>(proc)));
    else
        MessageBoxW(nullptr, L"Error finding process window.", nullptr, MB_OK);
}

auto hook::cleanup() noexcept -> void
{
    if (s_window and s_wndproc)
        SetWindowLongPtrA(s_window, GWLP_WNDPROC, reinterpret_cast<uintptr_t>(s_wndproc));

    if (s_present)
        swap_present();
}