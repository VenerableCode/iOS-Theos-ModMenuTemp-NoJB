#pragma once

class UserMenu {
public:
    UserMenu(const UserMenu&) = delete;

    static UserMenu& GetInstance() {
        static UserMenu Instance;
        return Instance;
    }

    //menus
    void DrawMenu();
    void RenderingMenu();
    void testmenu();

    //other
    void Initialize();

private:
    UserMenu() = default;
};

static UserMenu& Menu = UserMenu::GetInstance();