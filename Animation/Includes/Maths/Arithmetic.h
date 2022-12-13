#pragma once

namespace Maths
{
    // Rounds the given value to the nearest int.
    int roundInt(const float& val);

    // Rounds down the given value.
    int floorInt(const float& val);

    // Rounds up the given value.
    int ceilInt(const float& val);

    // Returns the sqare power of the given value.
    float sqpow(const float& val);

    // Returns 1 if the given value is positive or null, and -1 if it is negative.
    int signof(const float& val);

    // Converts the given angle from degrees to radians.
    float degToRad(const float& deg);

    // Converts the given angle from radians to degrees.
    float radToDeg(const float& rad);

    // Clamps the given value to be superior or equal to the minimum value and inferior or equal to the maximum value.
    float clamp(float val, const float& min, const float& max);

    // Clamps the given value to be inferior or equal to the maximum value.
    float clampUnder(float val, const float& max);

    // Clamps the given value to be superior or equal to the minimum value.
    float clampAbove(float val, const float& min);

    // Compute linear interpolation between start and dest for the parameter val (if 0 <= val <= 1: start <= return <= end).
    float lerp(const float& start, const float& dest, const float& val);

    // Compute the linear interpolation factor that returns val when lerping between start and end.
    float getLerp(const float& start, const float& dest, const float& val);

    // Remaps the given value from one range to another.
    float remap(const float& val, const float& inputStart, const float& inputEnd, const float& outputStart, const float& outputEnd);

    // Returns true if the given number is a power of 2.
    bool isPowerOf2(const int& val);

    // Returns the closest power of 2 that is inferior or equal to val.
    int getPowerOf2Under(const int& val);

    // Returns the closest power of 2 that is superior or equal to val.
    int getPowerOf2Above(const int& val);
}