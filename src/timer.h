#if !defined(TIMER_H)

#include <cmath>

#include "Constants.h"

enum class unit : uint8
{
    s,
    ms,
    us,
};

class time
{
private:
    real64 Time; // In seconds
public:
    static const real64 MillisecondsPerSecond;
    static const real64 MicrosecondsPerSecond;
    
    time operator=(const time& rhs);
    time operator+(const time& rhs);
    time operator-(const time& rhs);
    real64 operator/(const time& rhs);
    time operator%(const time& rhs);
    bool operator<(const time& rhs);
    bool operator>(const time& rhs);
    time operator+=(const time& rhs);
    
    time();
    time(real64, unit Unit = unit::s);
    
    real64 GetTime(unit UnitToReturn = unit::s);
};

class timer
{
private:
    static LARGE_INTEGER CountsPerSecond;
//    static uint64 ProgramStartTime;
    static time ProgramStartTime;

    bool32 Running;
    
    // LoopTime = 0 => Timer will not loop.
    time LoopTime;
    time StartTime;
public:
    timer();

    static void Initialize();
    static time GetAbsTime();
    static time GetProgramTime();

    void Start();
    void Stop();
    void Loop(time);
    time GetElapsedTime();
};

#define TIMER_H
#endif
