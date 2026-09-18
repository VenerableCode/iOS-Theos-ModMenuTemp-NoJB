#pragma once

#include "ImGuiDrawView.h"
#include "MenuLoad.h"

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"
#include "../ImGui/imgui_impl_metal.h"
#include "../utils/libtitanox/libtitanox/libtitanox.h"

#define NEON_AVAILABLE
#include "../utils/Wizardry/mystic.hh"

#if defined(KOMARU) //-DKOMARU
#include "../utils/Komaru/KMem.h"
#include "../utils/Komaru/KLog.hpp"
#endif

//engine-specifics
#if defined(UNREAL) && defined(UNITY)
    #error "[KOMARU]: cannot define both engines."
#elif defined(UNREAL)
    #include "../utils/Math/Unreal/Math.h"
    #include "../Source/Engines/UE4/Validity.h"
#elif defined(UNITY)
    #include "../utils/Math/Unity/Math.h"
#else
    #pragma message("[KOMARU]: Not targeting unreal engine or unity, defaulting to common; specify -DUNITY or -DUNREAL Makefile _CCFLAGS.")
    #include "../utils/Math/Common/Math.h"
#endif //in Makefile _CCFLAGS specify -DUNITY or -DUNREAL


#include <vector>
#include <map>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <functional>
#include <iostream>
#include <queue>
#include <thread>
#include <pthread/pthread.h>
#include <substrate.h>

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import <Foundation/Foundation.h>
#import <Security/Security.h>

#import <os/log.h>
#import <dlfcn.h>
#import <mach-o/dyld.h>
#import <stdio.h>
#import <mach/mach.h>

#define SCREEN_WIDTH [UIScreen mainScreen].bounds.size.width
#define SCREEN_HEIGHT [UIScreen mainScreen].bounds.size.height
#define SCREEN_SCALE [UIScreen mainScreen].scale
#define timer(sec) dispatch_after(dispatch_time(DISPATCH_TIME_NOW, sec * NSEC_PER_SEC), dispatch_get_main_queue(), ^

extern MenuInteraction* menuTouchView;
extern UIButton* InvisibleMenuButton;
extern UIButton* VisibleMenuButton;
extern UITextField* hideRecordTextfield;
extern UIView* hideRecordView;
extern ImFont* Font;

struct GlobalVariables
{
    static GlobalVariables& GetInstance() 
    {
        static GlobalVariables Instance;
        return Instance;
    }

    ImFont* Font;

    ImVec2 MenuSize   = ImVec2(0, 0);
    ImVec2 MenuOrigin = ImVec2(0, 0);

    bool StreamerMode = false;
    bool MoveMenu = false;

    bool testMenu = false;
    uintptr_t Base = 0;
};

static GlobalVariables& KTempVars = GlobalVariables::GetInstance();
