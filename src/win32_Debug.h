#if !defined(WIN32_DEBUG_H)

#include <string>

class Debug
{
public:
    static void DisplayCmdLine();
    
    template<typename type> static void WriteValue(type Value, std::string Label = "");
    static void WriteString(std::string StringToWrite);
    static void WriteLine(std::string StringToWrite);
    static void WriteError(std::string StringToWrite);
    static void WriteDebug(std::string StringToWrite);

    static uint32 DebugCount;
};

#define WIN32_DEBUG_H
#endif
