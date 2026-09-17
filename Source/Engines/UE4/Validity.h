#pragma once

#include <cstdint>

namespace UE4
{
    constexpr uint32_t RF_PendingKill     = 0x00008000;
    constexpr uint32_t RF_BeginDestroyed  = 0x00010000;
    constexpr uint32_t RF_FinishDestroyed = 0x00020000;

    inline bool IsPendingDestroy(uintptr_t addr)
    {
        if (!addr) return true;

        uint32_t flags = *reinterpret_cast<uint32_t*>(addr + 0x08);
        return (flags & RF_PendingKill) || (flags & RF_BeginDestroyed) || (flags & RF_FinishDestroyed);
    }

    inline bool IsValidUObject(uintptr_t addr)
    {
        if (!addr) return false;
        
        uint32_t flags = *reinterpret_cast<uint32_t*>(addr + 0x08);
        return !(flags & (RF_PendingKill | RF_BeginDestroyed | RF_FinishDestroyed));
    }
}