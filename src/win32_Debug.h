#if !defined(WIN32_DEBUG_H)

#include <string>

class Debug
{
public:
    template<typename type> static void WriteValue(type Value, std::string Label = "");
    static void WriteString(std::string StringToWrite);
    static void WriteError(std::string StringToWrite);
};

#define WIN32_DEBUG_H
#endif
