#include "Maths/Maths.h"
#include <cmath>
#include <cassert>
using namespace Maths;

// Rounds the given value to the nearest int.
int Maths::roundInt(const float& val) { return (int)round(val); }

// Rounds down the given value.
int Maths::floorInt(const float& val) { return (int)floor(val); }

// Rounds up the given value.
int Maths::ceilInt(const float& val) { return (int)ceil(val); }

// Returns the sqare power of the given value.
float Maths::sqpow(const float& val) { return val * val; }

// Returns 1 if the given value is positive or null, and -1 if it is negative.
int Maths::signof(const float& val) { if (val == 0) return 1; return (int)(val / abs((int)val)); }

// Converts the given angle from degrees to radians.
float Maths::degToRad(const float& deg) { return deg * (PI / 180.0f); }

// Converts the given angle from radians to degrees.
float Maths::radToDeg(const float& rad) { return rad * (180.0f / PI); }

// Clamps the given value to be superior or equal to the minimum value and inferior or equal to the maximum value.
float Maths::clamp(float val, const float& min, const float& max)
{
    assert(min <= max/*, "Unable to clamp: max < min."*/);
    if (val < min) val = min;
    if (val > max) val = max;
    return val;
}

// Clamps the given value to be inferior or equal to the maximum value.
float Maths::clampUnder(float val, const float& max) { if (val > max) val = max; return val; }

// Clamps the given value to be superior or equal to the minimum value.
float Maths::clampAbove(float val, const float& min) { if (val < min) val = min; return val; }

// Compute linear interpolation between start and dest for the parameter val (if 0 <= val <= 1: start <= return <= end).
float Maths::lerp(const float& start, const float& dest, const float& val)
{
    return start + val * (dest - start);
}

// Compute the linear interpolation factor that returns val when lerping between start and end.
float Maths::getLerp(const float& start, const float& dest, const float& val)
{
    if (dest - start != 0)
        return (val - start) / (dest - start);
    return 0;
}

// Remaps the given value from one range to another.
float Maths::remap(const float& val, const float& inputStart, const float& inputEnd, const float& outputStart, const float& outputEnd)
{
    return outputStart + (val - inputStart) * (outputEnd - outputStart) / (inputEnd - inputStart);
}

// Returns true if the given number is a power of 2.
bool Maths::isPowerOf2(const int& val)
{
    return val == (int)pow(2, (int)(log(val) / log(2)));
}

// Returns the closest power of 2 that is inferior or equal to val.
int Maths::getPowerOf2Under(const int& val)
{
    return (int)pow(2, (int)(log(val) / log(2)));
}

// Returns the closest power of 2 that is superior or equal to val.
int Maths::getPowerOf2Above(const int& val)
{
    if (isPowerOf2(val)) return (int)pow(2, (int)(log(val) / log(2)));
    else                 return (int)pow(2, (int)(log(val) / log(2) + 1)); // used to be (int)pow(2, (int)(log(val) / log(2)) + 1)
}