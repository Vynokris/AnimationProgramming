#pragma once
#include "Arithmetic.h"
#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "AngleAxis.h"
#include "Quaternion.h"
#include "Matrix.h"
#include "Transform.h"

#ifndef PI
#define PI 3.14159265358979323846f
#define TWOPI 6.283185307f
#define ONEDIVPI 0.318309886f
#define ONEDIVTWOPI 0.159154943f
#define PIDIV2 1.570796327f
#define PIDIV4 0.785398163f

#define MIN_FLOAT_VALUE 1.175494351e-38
#define MAX_FLOAT_VALUE 3.402823466e+38
#endif

namespace Maths
{
    // A point in 3D space with rendering data.
    struct Vertex
    {
        Vector3 pos;
        Vector2 uv;
        Vector3 normal;
    };

    // Holds indices for the vertex's data.
    struct TangentVertex
    {
        Vector3 pos;
        Vector2 uv;
        Vector3 normal;
        Vector3 tangent;
        Vector3 bitangent;
    };

    struct VertexIndices
    {
        uint32_t pos;
        uint32_t uv;
        uint32_t normal;
    };
}