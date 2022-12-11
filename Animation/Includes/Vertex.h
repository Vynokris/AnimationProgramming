#pragma once

#include "Vector3.h"
#include "Vector2.h"

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