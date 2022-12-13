#include "Dll/stdafx.h"

#include "Engine.h"
#include "Simulation.h"
#include "GlobalVariables.h"
#include "System\OperatingSystem.h"
#include "Application.h"
#include "Animation\Animation.h"
#include "Render\RenderPipeline.h"

using namespace WhiteBox;


void	Run( ISimulation* pSimulation, unsigned int width, unsigned int height )
{
 	WhiteBox::SGlobalVariables::Init();
 	WhiteBox::gVars->pSimulation = pSimulation;
 	WhiteBox::gVars->pOperatingSystem->Init( width, height );
}


void	SetSkinningPose(const float* boneMatrices, size_t boneCount)
{
	gVars->pApplication->pCharacterRenderNode->ApplySkinningPose(boneMatrices, boneCount);
}

size_t	GetSkeletonBoneCount()
{
	return gVars->pApplication->pCharacterSkel->GetBones().size();
}

const char*	GetSkeletonBoneName(int boneIndex)
{
	return (gVars->pApplication->pCharacterSkel->GetBones())[boneIndex].GetName().c_str();
}

int		GetSkeletonBoneIndex(const char* name)
{
	return (gVars->pApplication->pCharacterSkel->GetBoneNameToIndexMap())[String(name)];
}

int		GetSkeletonBoneParentIndex(int boneIndex)
{
	return (gVars->pApplication->pCharacterSkel->GetBones())[boneIndex].GetParentIndex();
}

void	GetSkeletonBoneLocalBindTransform(int boneIndex, float& posX, float& posY, float& posZ, float& quatW, float& quatX, float& quatY, float& quatZ)
{
	const Transform& t = gVars->pApplication->pCharacterSkel->m_localBindPose.m_boneTransforms[boneIndex];
	posX = t.position.x;
	posY = t.position.y;
	posZ = t.position.z;

	quatW = t.rotation.w;
	quatX = t.rotation.x;
	quatY = t.rotation.y;
	quatZ = t.rotation.z;
}


size_t	GetAnimKeyCount(const char* animName)
{

	CAnimationPtr pAnim = String(animName);

	return pAnim->m_animationTracks[1]->m_keyFrameCount;
}

void	GetAnimLocalBoneTransform(const char* animName, int boneIndex, int keyFrameIndex, float& posX, float& posY, float& posZ, float& quatW, float& quatX, float& quatY, float& quatZ)
{
	CAnimationPtr pAnim = String(animName);
	Transform t;
	if (pAnim->m_animationTracks[boneIndex])
	{
		pAnim->m_animationTracks[boneIndex]->GetKeyFrame2(keyFrameIndex, t);
	}

	posX = t.position.x;
	posY = t.position.y;
	posZ = t.position.z;

	quatW = t.rotation.w;
	quatX = t.rotation.x;
	quatY = t.rotation.y;
	quatZ = t.rotation.z;	
}

void	DrawLine(float x0, float y0, float z0, float x1, float y1, float z1, float r, float g, float b)
{
	gVars->pApplication->m_pRenderPipeline->DrawLine(Vec3(x0, y0, z0), Vec3(x1, y1, z1), Color(r, g, b));
}



