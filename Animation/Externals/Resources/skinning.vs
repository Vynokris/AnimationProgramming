// ----- Input variables ----- //

in lowp vec3 inPosition;
in lowp vec3 inNormal;
in lowp vec4 boneIndices;
in lowp vec4 boneWeights;


// ----- Output variables ----- //

smooth out vec2 texCoord;
smooth out vec3 outNormal;


// ----- Uniform variables ----- //

uniform SceneMatrices
{
    uniform mat4 projectionMatrix;
} sm;

uniform mat4 modelViewMatrix;

uniform SkinningMatrices
{
    uniform mat4 mat[64];
} skin;


// ----- Vertex shader ----- //

void main(void)
{
    vec4 outPosition = vec4(inPosition, 1.0f);

    // Transform the vertice's position and normal with the bone matrices.
    outPosition =    (skin.mat[int(boneIndices.x)]  * outPosition) * boneWeights.x + 
                     (skin.mat[int(boneIndices.y)]  * outPosition) * boneWeights.y + 
                     (skin.mat[int(boneIndices.z)]  * outPosition) * boneWeights.z + 
                     (skin.mat[int(boneIndices.w)]  * outPosition) * boneWeights.w;
    outNormal = (mat3(skin.mat[int(boneIndices.x)]) * outNormal  ) * boneWeights.x + 
                (mat3(skin.mat[int(boneIndices.y)]) * outNormal  ) * boneWeights.y + 
                (mat3(skin.mat[int(boneIndices.z)]) * outNormal  ) * boneWeights.z + 
                (mat3(skin.mat[int(boneIndices.w)]) * outNormal  ) * boneWeights.w;

    // Transform the vertice's position and normal with the world, view, and projection matrices.
    outPosition = sm.projectionMatrix * (modelViewMatrix * outPosition);
    outNormal   = mat3(modelViewMatrix) * inNormal;

    // Output the vertice's position and normal.
    gl_Position = outPosition;
    outNormal   = normalize(outNormal);
}
