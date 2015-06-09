#include "win32_Debug.h"

#include <iostream>

void
Debug::DisplayCmdLine()
{
    AllocConsole();
    freopen("conin$","r",stdin);
    freopen("conout$","w",stdout);
    freopen("conout$","w",stderr);
    printf("Debugging Window:\n");
}

template<typename type> void
Debug::WriteValue(type Value, std::string Label)
{
    if(std::is_integral<type>())
    {
        printf("%s: %d\n", Label.c_str(), Value);
    }
    else
    {
        printf("%s: %f\n", Label.c_str(), Value);        
    }
}

void
Debug::WriteString(std::string StringToWrite)
{
    printf(StringToWrite.c_str());
}

void
Debug::WriteError(std::string StringToWrite)
{
    printf(("ERROR: " + StringToWrite + "\n").c_str());
}
