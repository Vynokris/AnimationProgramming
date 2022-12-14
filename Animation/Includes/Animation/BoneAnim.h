#pragma once
#include "Maths/Transform.h"

constexpr float KEYFRAME_DURATION = 1/30.f;

constexpr const char* WALK_ANIMATION = "ThirdPersonWalk.anim";
constexpr const char* RUN_ANIMATION  = "ThirdPersonRun.anim";

class BoneAnim
{
private:
	const int   boneIndex;
	const char* curAnimName   = "";
	int         curKeyFrame   = -1;
	float       keyFrameTimer = 0;
	Transform   poseTransform;
	Transform   prevPoseTransform;
	
public:
	BoneAnim(const int& boneId) : boneIndex(boneId) {}
	
	void SetCurrentAnimation(const char* animName);
	void UpdateTimer		(const float& deltaTime);
	void UpdatePoseTransform();

	Mat4 GetPoseLocalMat() const;
	Mat4 GetParentMat   () const;
	void SetParentMat   (const Mat4& worldMat);
};
