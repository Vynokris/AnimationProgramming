#pragma once
#include "Maths/Transform.h"

constexpr float KEYFRAME_DURATION = 0.05f;

constexpr const char* WALK_ANIMATION = "ThirdPersonWalk.anim";
constexpr const char* RUN_ANIMATION  = "ThirdPersonRun.anim";

class Animation
{
private:
	const int   boneIndex;
	const char* curAnimName   = "";
	int         curKeyFrame   = -1;
	float       keyFrameTimer = 0;
	Transform   poseTransform;
	Transform   prevPoseTransform;
	
public:
	Animation(const int& boneId) : boneIndex(boneId) {}
	
	void SetCurrentAnimation(const char* animName);
	void UpdateTimer		(const float& deltaTime);
	void UpdatePoseTransform();
	
	Mat4 GetPoseMat() const;
};
