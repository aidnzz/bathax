#include <thread>
#include <windows.h>

#include "hook.hpp"

auto APIENTRY DllMain([[maybe_unused]] HINSTANCE instance, DWORD reason, [[maybe_unused]] LPVOID reserved) -> BOOL
{
    DisableThreadLibraryCalls(instance);

    if (reason == DLL_PROCESS_ATTACH)
        std::thread(hook::initialise).detach();

    return true;
}