#ifndef __ENGINE_H__
#define __ENGINE_H__

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport) 
#else
#define ENGINE_API __declspec(dllimport) 
#endif


namespace WhiteBox
{
    class COperatingSystem;
    class CResourceManager;
}


ENGINE_API void	Run(class ISimulation* pSimulation, unsigned int width, unsigned int height);

ENGINE_API void	       SetSkinningPose(const float* boneMatrices, size_t boneCount);
ENGINE_API size_t      GetSkeletonBoneCount();
ENGINE_API const char* GetSkeletonBoneName(size_t boneIndex);
ENGINE_API size_t      GetSkeletonBoneIndex(const char* name);
ENGINE_API size_t      GetSkeletonBoneParentIndex(size_t boneIndex);
ENGINE_API void	       GetSkeletonBoneLocalBindTransform(size_t boneIndex, float& posX, float& posY, float& posZ, float& quatW, float& quatX, float& quatY, float& quatZ);

ENGINE_API size_t GetAnimKeyCount(const char* animName);
ENGINE_API void	  GetAnimLocalBoneTransform(const char* animName, size_t boneIndex, size_t keyFrameIndex, float& posX, float& posY, float& posZ, float& quatW, float& quatX, float& quatY, float& quatZ);

ENGINE_API void Log(const char* channel, const char* format, ...);

ENGINE_API void* GetImGuiContext();
ENGINE_API WhiteBox::COperatingSystem* GetOperatingSystem();
ENGINE_API WhiteBox::CResourceManager* GetResourceManager();

ENGINE_API void	DrawLine(float x0, float y0, float z0, float x1, float y1, float z1, float r, float g, float b);


#endif