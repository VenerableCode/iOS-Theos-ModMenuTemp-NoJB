#include "BasicHacks.h"
#include "../MenuLoad/Includes.h"

bool running = true;

void BasicHacks::HacksThread()
{
    while (running)
    {
        KTempVars.Base = KMEM::scanner::FindFirstBase();

        if(!KTempVars.Base)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}



void BasicHacks::Initialize()
{
    std::thread(HacksThread).detach();
}