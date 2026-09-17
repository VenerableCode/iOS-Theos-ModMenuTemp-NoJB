#pragma once

class BasicHacks
{
    
public:
    BasicHacks(const BasicHacks&) = delete;

    static BasicHacks& GetInstance()
    {
        static BasicHacks instance;
        return instance;
    }

    static void HacksThread();
    void Initialize();

private:
    BasicHacks() = default;
};

static BasicHacks& R_BasicCheats = BasicHacks::GetInstance(); //we init in ImGuiDrawVIew.xm
