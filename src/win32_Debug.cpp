#include "win32_Debug.h"

template<typename type> void
Debug::WriteValue(type Value, std::string Label)
{
    // TODO(tyler): Unsafe. If the value is longer than 200 characters, this will segfault.
    char DebugString[200];
    sprintf(DebugString, "%s: %9.7f\n", Label, Value);
    OutputDebugStringA(DebugString);
}

void
Debug::WriteString(std::string StringToWrite)
{
    OutputDebugStringA((LPCTSTR)StringToWrite.c_str());
}
