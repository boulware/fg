#include <windows.h>

#include "Globals.h"

// External libraries

#include "SFML/System.hpp"
#include "SFML/Window.hpp"

// ------------------

#include "win32_Debug.h"
#include "game.h"

#include "win32_Debug.cpp"
#include "game.cpp"
#include "collision_box.cpp"
#include "skeleton.cpp"
#include "fighter.cpp"
#include "sprite.cpp"

LRESULT CALLBACK
MainWindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
    switch(Message)
    {
        case WM_CLOSE:
        {
            Global::Game->IsRunning = false;

            PostQuitMessage(0);
        } break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC DeviceContext = BeginPaint(Window, &ps);

            if(Global::Game) Global::Game->Blit();

            EndPaint(Window, &ps);
        } break;
        default:
        {
            return DefWindowProcA(Window, Message, WParam, LParam);
        } break;
    }

    return(0);
}

HWND
SetUpWindow(HINSTANCE Instance)
{
    WNDCLASSEX MainWindowClass = {};
    MainWindowClass.cbSize = sizeof(WNDCLASSEX);
    MainWindowClass.style = CS_HREDRAW|CS_VREDRAW;
    MainWindowClass.lpfnWndProc = MainWindowProc;
    MainWindowClass.hInstance = Instance;
    MainWindowClass.lpszClassName = "MainWindowClass";

    RegisterClassExA(&MainWindowClass);
    
    HWND Window = CreateWindowEx(0,
                                 "MainWindowClass", "Window Name",
                                 WS_VISIBLE|WS_SYSMENU,
                                 CW_USEDEFAULT, CW_USEDEFAULT,
                                 Const::WindowWidth, Const::WindowHeight,
                                 0, 0,
                                 Instance, 0);
    
    RECT rc;
    GetWindowRect(Window, &rc);

    DWORD dwStyle = GetWindowLongPtr(Window, GWL_STYLE);
    DWORD dwExStyle = GetWindowLongPtr(Window, GWL_EXSTYLE);
    HMENU menu = GetMenu(Window);
    
    AdjustWindowRectEx(&rc, dwStyle, menu ? TRUE : FALSE, dwExStyle);

    SetWindowPos(Window, 0, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
                 SWP_NOMOVE|SWP_NOZORDER);
    HCURSOR WindowCursor = LoadCursor(Instance, IDC_ARROW);
    SetCursor(WindowCursor);

    return Window;
}

int CALLBACK
WinMain(
    HINSTANCE Instance,
    HINSTANCE PrevInstance,
    LPSTR     CommandLine,
    int       CommandShow)
{
    Debug::DisplayCmdLine();
    
    Global::Window.create(sf::VideoMode(Const::WindowWidth, Const::WindowHeight, 8 * Const::BytesPerPixel), "fg");
    Global::Game = new game;

    uint8 Loops;
    sf::Clock GameClock;
    sf::Time NextGameTick = GameClock.getElapsedTime();

    while(Global::Game->IsRunning)
    {
        sf::Event Event;
        while(Global::Window.pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed)
            {
                Global::Game->IsRunning = false;
                Global::Window.close();
            }
        }
        
        if(Global::Game->Paused == false)
        {
            Loops = 0;
            while(GameClock.getElapsedTime() > NextGameTick && Loops < Global::MaxFrameSkip)
            {
                Global::Game->HandleInput();
                Global::Game->Update();

                NextGameTick += Global::FrameTime;
                Loops++;
            }
        }
        else
        {
            // TODO(tyler): This frame advance does not work with WasPressed things in input_buffer.
            // Reason unknown. Fix ASAP.
            while(GameClock.getElapsedTime() > NextGameTick)
            {
                Global::Game->HandleInput();

                NextGameTick += Global::FrameTime;
            }
        }
        
        Global::Game->Blit(); 
    }
}

