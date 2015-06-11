#include "win32_Debug.h"

#include <iostream>

uint32 Debug::DebugCount = 0;
uint32 Debug::ErrorCount = 0;
bool32 Debug::StartedUp = false;
std::string Debug::StartupErrors = "Startup:\n";

void
Debug::DisplayCmdLine()
{
    AllocConsole();
    freopen("conin$","r",stdin);
    freopen("conout$","w",stdout);
    freopen("conout$","w",stderr);
    printf(StartupErrors.c_str());
    printf("---main starts----\n");
    
    StartedUp = true;
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
    if(StartedUp)
    {    
        printf(StringToWrite.c_str());
    }
    else
    {
        StartupErrors += StringToWrite;
    }
}

void
Debug::WriteLine(std::string StringToWrite)
{
    std::string FullString = StringToWrite + "\n";
    
    if(StartedUp)
    {
        printf(FullString.c_str());
    }
    else
    {
        StartupErrors += FullString;
    }
}

void
Debug::WriteError(std::string StringToWrite)
{
    std::string FullString = "ERROR[" + std::to_string(ErrorCount++) + "]: " + StringToWrite + "\n";
    
    if(StartedUp)
    {
        printf(FullString.c_str());
    }
    else
    {
        StartupErrors += FullString;
    }
}

void
Debug::WriteDebug(std::string StringToWrite)
{
    std::string FullString = "DEBUG[" + std::to_string(DebugCount++) + "]: " + StringToWrite + "\n";
    
    if(StartedUp)
    {
        printf(FullString.c_str());
    }
    else
    {
        StartupErrors += FullString;
    }
}
