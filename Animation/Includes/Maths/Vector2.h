#pragma once

namespace Maths
{
    // Vector class that holds values for x and y (2 dimensions).
    class Vector2
    {
    public:
        // -- Attributes -- //
        float x, y;

        // -- Constructors & Destructor -- //
        Vector2();                                                           // Null vector.
        Vector2(const float& _x, const float& _y);                           // Vector with 2 coordinates.
        Vector2(const Vector2& p1, const Vector2& p2);                       // Vector from 2 points.
        Vector2(const float& rad, const float& length, const bool& isAngle); // Vector from angle (useless bool).
        ~Vector2() {}

        // -- Operators -- //

                              void    operator= (const Vector2& v);
        template <typename T> bool    operator==(const T& val) const;
        template <typename T> bool    operator!=(const T& val) const;
        template <typename T> Vector2 operator+ (const T& val) const;
        template <typename T> Vector2 operator- (const T& val) const;
        template <typename T> Vector2 operator* (const T& val) const;
        template <typename T> Vector2 operator/ (const T& val) const;
        template <typename T> void    operator+=(const T& val);
        template <typename T> void    operator-=(const T& val);
        template <typename T> void    operator*=(const T& val);
        template <typename T> void    operator/=(const T& val);
                              float   operator& (const Vector2& v) const;
                              float   operator^ (const Vector2& v) const;
                              Vector2 operator- ()             const;

        // -- Methods -- //

        // Returns the middle of the given vector.
        Vector2 getMiddle() const;

        // Returns the length of the given vector.
        float getLength() const;
        // Modifies the length of the given vector to correspond to the given value.
        void setLength(const float& length);

        // Normalizes the given vector so that its length is 1.
        void normalize();
        // Normalizes the given vector so that its length is 1.
        Vector2 getNormalized() const;

        // Negates both of the coordinates of the given vector.
        void negate();

        // Copies the signs from the source vector to the destination vector.
        void copysign(const Vector2& source);
        // Copies the signs from the source vector to the destination vector.
        Vector2 getCopiedSign(const Vector2& source) const;

        // Returns the normal of a given vector.
        Vector2 getNormal() const;

        // Interprets the vector as a point and returns the distance to another point.
        float getDistanceFromPoint(const Vector2& p) const;

        // Returns the angle (in radians) of the given vector.
        float getAngle() const;

        // Returns the angle (in radians) between two vectors.
        float getAngleWithVector2(const Vector2& v) const;

        // Rotates the given vector by the given angle.
        void rotate(const float& angle);

        // Rotates the point around the given pivot point by the given angle (in rad).
        void rotateAsPoint(const Vector2& pivot, const float& angle);
    };

    // Calculates linear interpolation for a value from a start point to an end point.
    Vector2 point2Lerp(const float& val, const Vector2& start, const Vector2& end);
}

#include "Vector2.inl"
