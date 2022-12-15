#ifndef __ENGINE_H__
#define __ENGINE_H__

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport) 
#else
#define ENGINE_API __declspec(dllimport) 
#endif

ENGINE_API void	       Run(class ISimulation* pSimulation, unsigned int width, unsigned int height);
ENGINE_API void	       SetSkinningPose(const float* boneMatrices, size_t boneCount);
ENGINE_API size_t      GetSkeletonBoneCount();
ENGINE_API const char* GetSkeletonBoneName(int boneIndex);
ENGINE_API int	       GetSkeletonBoneIndex(const char* name);
ENGINE_API int	       GetSkeletonBoneParentIndex(int boneIndex);
ENGINE_API void	       GetSkeletonBoneLocalBindTransform(int boneIndex, float& posX, float& posY, float& posZ, float& quatW, float& quatX, float& quatY, float& quatZ);
ENGINE_API size_t      GetAnimKeyCount(const char* animName);
ENGINE_API void	       GetAnimLocalBoneTransform(const char* animName, int boneIndex, int keyFrameIndex, float& posX, float& posY, float& posZ, float& quatW, float& quatX, float& quatY, float& quatZ);
ENGINE_API void        Log(const char* channel, const char* format, ...);
ENGINE_API void*       GetImGuiContext();
ENGINE_API void	       DrawLine(float x0, float y0, float z0, float x1, float y1, float z1, float r, float g, float b);

#endif