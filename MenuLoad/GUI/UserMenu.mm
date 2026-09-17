#include "UserMenu.h"
#include "../Includes.h"
#include "../TextInput.h"

#include <thread>
#include <string>
#include <atomic>


void UserMenu::DrawMenu()
{
    ImVec2 WindowSize = ImVec2(275, 200);

    ImGui::SetNextWindowSize(WindowSize, ImGuiCond_Once);

    ImVec2 WindowPosition = ImVec2(
        (SCREEN_WIDTH - WindowSize.x) / 2,
        (SCREEN_HEIGHT - WindowSize.y) / 2
    );

    ImGui::SetNextWindowPos(WindowPosition, ImGuiCond_Once);

    ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
    if (!KTempVars.MoveMenu) WindowFlags |= ImGuiWindowFlags_NoMove;

    if (ImGui::Begin("KomaruTemp", nullptr, WindowFlags))
    {
        ImGuiWindow* CurrentWindow = ImGui::GetCurrentWindow();

        KTempVars.MenuSize   = CurrentWindow->Size;
        KTempVars.MenuOrigin = CurrentWindow->Pos;

        ImGui::Text("%s", MYSTIFY("Hello, Komaru!").c_str()); //xor strings with mystic.hh

        ImGui::Checkbox("testmenu", &KTempVars.testMenu);

        if(ImGui::Button("PrintToFileButton"))
        {
            KLOG::MsgToFile("Komaru.txt", "Clicked!");
        }

        ImGui::Text("Base: 0x%llX", (unsigned long long)KTempVars.Base);




        ImGui::Checkbox("Move Menu", &KTempVars.MoveMenu);
        ImGui::SameLine();
        ImGui::Checkbox("Streamer Mode", &KTempVars.StreamerMode);
    }

    ImGui::End();
}


void UserMenu::testmenu() {
    if(KTempVars.testMenu) {
        ImGui::Begin("TestMenu", NULL, ImGuiWindowFlags_None);
            ImGui::Text("%s", MYSTIFY("Komaru!").c_str()); //another mystify example

            static std::string TestInput;

            ImGuiInput::Text(
                "TestInput",
                TestInput
            );


        ImGui::End();
    }
}


void UserMenu::RenderingMenu()
{
    ImGui::Begin(
        "RenderMenu",
        nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoInputs
    );

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    //draw here
    
    ImGui::End();
}

void UserMenu::Initialize() //init menus
{
    DrawMenu();
    testmenu(); 
    RenderingMenu();
}
