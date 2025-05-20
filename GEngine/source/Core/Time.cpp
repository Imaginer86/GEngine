#include "Time.h"

#include <chrono>

long long Core::GetTickCount()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}
