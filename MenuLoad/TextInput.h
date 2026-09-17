#pragma once

#include <string>
#include <cstring>
#include <unordered_map>
#include <UIKit/UIKit.h>
#include "../../../ImGui/imgui.h"

@interface KeyboardInputField : UITextField

@property(nonatomic, assign) void (*onChanged)(const char *);
@property(nonatomic, assign) void (*onReturn)(void);

@end

@implementation KeyboardInputField

- (instancetype)init
{
    self = [super initWithFrame:CGRectMake(0, 0, 1, 1)];

    if (self)
    {
        self.backgroundColor = UIColor.clearColor;
        self.textColor = UIColor.clearColor;
        self.tintColor = UIColor.clearColor;
        self.alpha = 0.01f;

        self.autocorrectionType = UITextAutocorrectionTypeNo;
        self.spellCheckingType = UITextSpellCheckingTypeNo;
        self.autocapitalizationType = UITextAutocapitalizationTypeNone;
        self.returnKeyType = UIReturnKeyDone;

        [self addTarget:self
                  action:@selector(textFieldDidChange:)
        forControlEvents:UIControlEventEditingChanged];
    }

    return self;
}

- (void)textFieldDidChange:(UITextField *)textField
{
    if (self.onChanged)
        self.onChanged(textField.text.UTF8String ?: "");
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    if (self.onReturn)
        self.onReturn();

    [textField resignFirstResponder];

    return YES;
}

@end

namespace ImGuiInput
{

struct State
{
    KeyboardInputField *field = nil;
    std::string *activeText = nullptr;

    bool keyboardVisible = false;
    bool ignoreNextChange = false;

    static State& Get()
    {
        static State state;
        return state;
    }

    void EnsureField()
    {
        if (field)
            return;

        field = [[KeyboardInputField alloc] init];

        field.onChanged = [](const char *text)
        {
            State &state = State::Get();

            if (!state.activeText || state.ignoreNextChange)
                return;

            *state.activeText = text ? text : "";
        };

        field.onReturn = []()
        {
            State &state = State::Get();

            state.keyboardVisible = false;
            state.activeText = nullptr;
        };

        UIWindow *window = nil;

        for (UIScene *scene in
             UIApplication.sharedApplication.connectedScenes)
        {
            if (scene.activationState !=
                UISceneActivationStateForegroundActive)
                continue;

            if (![scene isKindOfClass:[UIWindowScene class]])
                continue;

            UIWindowScene *windowScene = (UIWindowScene *)scene;

            for (UIWindow *candidate in windowScene.windows)
            {
                if (candidate.isKeyWindow)
                {
                    window = candidate;
                    break;
                }
            }

            if (window)
                break;
        }

        if (!window)
            window = UIApplication.sharedApplication.windows.firstObject;

        if (window)
            [window addSubview:field];
    }
};

inline void BeginEditing(std::string &text)
{
    State &state = State::Get();

    state.EnsureField();

    if (state.activeText == &text && state.keyboardVisible)
        return; // already editing this field - don't reset cursor/selection

    state.activeText = &text;
    state.ignoreNextChange = true;

    state.field.text =
        [NSString stringWithUTF8String:text.c_str()];

    state.field.selectedTextRange =
        [state.field
            textRangeFromPosition:state.field.endOfDocument
            toPosition:state.field.endOfDocument];

    state.ignoreNextChange = false;
    state.keyboardVisible = true;

    [state.field becomeFirstResponder];
}

inline void HideKeyboard()
{
    State &state = State::Get();

    if (state.field)
        [state.field resignFirstResponder];

    state.activeText = nullptr;
    state.keyboardVisible = false;
}

// Renders a text field backed by the native iOS keyboard.
//
// While a field is being actively edited, we deliberately do NOT use
// ImGui::InputText - even in read-only mode it draws its own blinking
// text cursor, and that cursor has no way to track the native
// UITextField's real cursor position (ImGui isn't told where it is), so
// it just sits static except for mouse-driven repositioning. Instead we
// draw a plain box + text manually (no cursor at all) and use an
// invisible button purely to detect taps.
inline bool Text(
    const char *label,
    std::string &text,
    ImGuiInputTextFlags flags = 0)
{
    State &state = State::Get();

    state.EnsureField();

    ImGuiID id = ImGui::GetID(label);

    const bool isActiveField =
        (state.activeText == &text && state.keyboardVisible);

    ImGui::PushID(label);

       if (isActiveField)
    {
        ImGuiStyle &style = ImGui::GetStyle();

        ImVec2 size = ImVec2(ImGui::CalcItemWidth(), ImGui::GetFrameHeight());
        ImVec2 pos = ImGui::GetCursorScreenPos();
        ImVec2 maxPos = ImVec2(pos.x + size.x, pos.y + size.y);

        ImGui::InvisibleButton("##InputArea", size);

        if (ImGui::GetIO().MouseClicked[0])
            HideKeyboard(); // any click while editing dismisses the keyboard

        ImDrawList *drawList = ImGui::GetWindowDrawList();

        drawList->AddRectFilled(
            pos,
            maxPos,
            ImGui::GetColorU32(ImGuiCol_FrameBgActive),
            style.FrameRounding
        );

        drawList->PushClipRect(pos, maxPos, true);

        drawList->AddText(
            ImVec2(pos.x + style.FramePadding.x, pos.y + style.FramePadding.y),
            ImGui::GetColorU32(ImGuiCol_Text),
            text.c_str()
        );

        drawList->PopClipRect();
    }
    else
    {
        char buffer[4096];

        constexpr size_t MaxLength = sizeof(buffer) - 1;

        size_t length = text.size();

        if (length > MaxLength)
            length = MaxLength;

        memcpy(buffer, text.data(), length);
        buffer[length] = '\0';

        ImGui::InputText("##Input", buffer, sizeof(buffer), flags);

        if (ImGui::IsItemClicked() || ImGui::IsItemActivated())
        {
            text = buffer;
            BeginEditing(text);
        }
    }

    ImGui::PopID();

    // Neither path above reports "changed" the way a normal InputText
    // would, so track each field's last-seen value ourselves to preserve
    // the original return-value contract for callers.
    static std::unordered_map<ImGuiID, std::string> lastValues;

    std::string &last = lastValues[id];
    bool changed = (last != text);
    last = text;

    return changed;
}

}