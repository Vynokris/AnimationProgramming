#pragma once

namespace Maths
{
    class Vector3;
    class Quaternion;
    typedef Matrix<4, 4> Mat4;

    // AngleAxis class that holds values for an angle and an axis of rotation.
    class AngleAxis
    {
    public:
        float   angle;
        Vector3 axis;

        // -- Constructors -- //
        AngleAxis();                                          // Default constructor.
        AngleAxis(const float& _angle, const Vector3& _axis); // Angle-axis from angle and vector.
        AngleAxis(const Quaternion& quaternion);              // Angle-axis from quaternion.
        AngleAxis(const Mat4&       matrix    );              // Angle-axis from rotation matrix.

        // -- Static constructors -- //
        static AngleAxis FromQuaternion(const Quaternion& quaternion); // Angle-axis from quaternion.
        static AngleAxis FromMatrix    (const Mat4&       matrix    ); // Angle-axis from rotation matrix.

        // -- Conversions -- //
        Quaternion  ToQuaternion() const;                         // Returns the quaternion that corresponds to this angle-axis rotation.
        Mat4        ToMatrix    () const;                         // Returns the rotation matrix that corresponds to this angle-axis rotation.
        std::string ToString    (const int& precision = 2) const; // Returns the contents of the angle-axis rotation as a string.
    };
}
