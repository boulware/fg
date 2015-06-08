#include "timer.h"

const real64 time::MillisecondsPerSecond = 1000;
const real64 time::MicrosecondsPerSecond = 1000000;

time time::operator=(const time& rhs)
{
    Time = rhs.Time;

    return *this;
}

time time::operator+(const time& rhs)
{
    return time(Time + rhs.Time);
}

time time::operator-(const time& rhs)
{
    return time(Time - rhs.Time);
}

real64 time::operator/(const time& rhs)
{
    return Time / rhs.Time;
}

time time::operator%(const time& rhs)
{
    return time(fmod(Time, rhs.Time));
}

bool time::operator<(const time& rhs)
{
    return Time < rhs.Time;
}

bool time::operator>(const time& rhs)
{
    return Time > rhs.Time;
}

time time::operator+=(const time& rhs)
{
    Time += rhs.Time;

    return *this;
}

time::time()
        :
        Time(0)
{
}

time::time(real64 Value, unit Unit)
{
    switch(Unit)
    {
        case(unit::s):
        {
            Time = Value;
        } break;
        case(unit::ms):
        {
            Time = Value / MillisecondsPerSecond;
        } break;
        case(unit::us):
        {
            Time = Value / MicrosecondsPerSecond;
        } break;
        default:
        {
            Time = 0;
        } break;
    }
}

real64
time::GetTime(unit UnitToReturn)
{
    switch(UnitToReturn)
    {
        case(unit::s):
        {
            return Time;
        } break;
        case(unit::ms):
        {
            return Time * MillisecondsPerSecond;
        } break;
        case(unit::us):
        {
            return Time * MicrosecondsPerSecond;
        } break;
        default:
        {
            return -1.0f;
        } break;
    }
}

LARGE_INTEGER timer::CountsPerSecond;
time timer::ProgramStartTime;

timer::timer() : Running(false), LoopTime(), StartTime()
{
}

void
timer::Initialize()
{
    QueryPerformanceFrequency(&CountsPerSecond);

    timer::ProgramStartTime = GetAbsTime();
    //ProgramStartTime(GetAbsTime());
}

time
timer::GetAbsTime()
{
    LARGE_INTEGER Counts;
    QueryPerformanceCounter(&Counts);

    uint64 CurrentTimeInMicroseconds = (Counts.QuadPart * time::MicrosecondsPerSecond) / CountsPerSecond.QuadPart;

    return time(CurrentTimeInMicroseconds, unit::us);
}

time
timer::GetProgramTime()
{
    return GetAbsTime() - ProgramStartTime;
}

void
timer::Start()
{
    Running = true;
    StartTime = GetAbsTime();
}

void
timer::Stop()
{
    Running = false;
}

void
timer::Loop(time LoopTime)
{
    this->LoopTime = LoopTime;
}

time
timer::GetElapsedTime()
{
    if(Running == (bool32)true)
    {
        time CurrentTime = GetAbsTime();
    
        if(LoopTime.GetTime() == 0)
        {    
            return CurrentTime - StartTime;
        }
        else
        {
            return (CurrentTime - StartTime) % LoopTime;
        }
    }
    else
    {
        return time();
    }
}
