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

        AngleAxis();
        AngleAxis(const float& _angle, const Vector3& _axis);

        Quaternion ToQuaternion() const;
        Mat4       ToMatrix    () const;
    };
}
