#pragma once
#include "Maths/Transform.h"
class Animator;

constexpr float KEYFRAME_DURATION = 1/30.f;

constexpr const char* WALK_ANIMATION = "ThirdPersonWalk.anim";
constexpr const char* RUN_ANIMATION  = "ThirdPersonRun.anim";

class BoneAnim
{
private:
	Animator&   animator;
	const int   boneIndex;
	int         curKeyframe = 0;
	Transform   poseTransform;
	Transform   prevPoseTransform;
	
public:
	BoneAnim(const int& boneId, Animator& skeletonAnimator) : animator(skeletonAnimator), boneIndex(boneId) {}
	
	void UpdatePoseTransform();
	Mat4 GetPoseLocalMat() const;
	Mat4 GetParentMat   () const;
	void SetParentMat   (const Mat4& worldMat);
};
