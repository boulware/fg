#if !defined(INPUT_BUFFER_H)

#include "Globals.h"
#include <vector>

struct button
{   
    button(int);
    void Clear();
    
    int VKCode;
    
    bool32 IsDown;
    bool32 WasPressed;
    bool32 WasReleased;
};

button::button(int VKCode)
        :
        VKCode(VKCode), IsDown(0), WasPressed(0), WasReleased(0)
{
}

void
button::Clear()
{
    IsDown = 0;
    WasPressed = 0;
    WasReleased = 0;
}

struct input_buffer
{
    input_buffer();
    input_buffer operator=(const input_buffer& rhs);

    int32 MouseX;
    int32 MouseY;

    // TODO(tyler): Replace these separate definitions with a multi-key map
    // (multi-key so that multiple keys can be mapped to one button?)
    button MoveLeft;
    button MoveRight;
    button Jump;
    button Crouch;

    button FrameStop;
    button FrameAdvance;

    button HitboxToggle;

    std::vector<button*> Buttons;
};

input_buffer::input_buffer()
        :
        MouseX(0), MouseY(0),
        MoveLeft(0x25), MoveRight(0x27),
        Jump(0x26), Crouch(0x28),
        FrameStop(VK_F1),
        FrameAdvance(VK_F2),
        HitboxToggle(VK_F5)
{
    Buttons.push_back(&MoveLeft);
    Buttons.push_back(&MoveRight);
    Buttons.push_back(&Jump);
    Buttons.push_back(&Crouch);
    Buttons.push_back(&FrameStop);
    Buttons.push_back(&FrameAdvance);
    Buttons.push_back(&HitboxToggle);
}

input_buffer input_buffer::operator=(const input_buffer& rhs)
{
    this->MouseX = rhs.MouseX;
    this->MouseY = rhs.MouseY;

    for(uint8 ButtonIndex = 0; ButtonIndex < this->Buttons.size(); ButtonIndex++)
    {
        *(this->Buttons[ButtonIndex]) = *(rhs.Buttons[ButtonIndex]);
    }

    return *this;
}

void
ClearInputBuffer(input_buffer* Input)
{
    Input->MouseX = 0;
    Input->MouseY = 0;
    for(auto &elem : Input->Buttons)
    {
        elem->Clear();
    }
}

void
FetchAndParseInput(input_buffer* ThisFrameInput, input_buffer* PrevFrameInput)
{
    *PrevFrameInput = *ThisFrameInput;
    ClearInputBuffer(ThisFrameInput);

    // NOTE(tyler): For now, I'm forgoing a (safer) range-based loop in order to be able to cross-reference
    // button elements between different input buffers using a ButtonIndex.
    /*
    for(auto &elem : ThisFrameInput->Buttons)
    {
        if(GetKeyState(elem.VKCode) && 0x8000)
        {
            elem.IsDown = true;
            if(PrevFrameInput->
        }
    }
    */
    for(uint8 ButtonIndex = 0; ButtonIndex < ThisFrameInput->Buttons.size(); ButtonIndex++)
    {
        button* DestButton = ThisFrameInput->Buttons[ButtonIndex];
        button* PrevButton = PrevFrameInput->Buttons[ButtonIndex];
        if(GetKeyState(DestButton->VKCode) & 0x8000)
        {
            DestButton->IsDown = true;
            if(PrevButton->IsDown == false)
            {
                DestButton->WasPressed = true;
            }
        }
        else
        {
            DestButton->IsDown = false;
            if(PrevButton->IsDown == (bool32)true) DestButton->WasReleased = true;
        }
    }

    POINT CursorPosition = {};
    GetCursorPos(&CursorPosition);

    /*
    ScreenToClient(Global::Window, &CursorPosition);
    
    ThisFrameInput->MouseX = CursorPosition.x;
    ThisFrameInput->MouseY = CursorPosition.y;
    */
}

#define INPUT_BUFFER_H
#endif
