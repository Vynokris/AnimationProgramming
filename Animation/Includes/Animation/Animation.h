#pragma once
#include "Maths/Transform.h"

constexpr float KEYFRAME_DURATION = 0.5f;

constexpr const char* WALK_ANIMATION = "ThirdPersonWalk.anim";
constexpr const char* RUN_ANIMATION  = "ThirdPersonRun.anim";

class Animation
{
private:
	const char*      curAnimName   = "";
	int              curKeyFrame   = -1;
	float            keyFrameTimer = 0;
	Maths::Transform poseTransform;
	Maths::Transform prevPoseTransform;
	
public:
	void SetCurrentAnimation(const char* animName, const int& boneIndex);
	void UpdateTimer		(const float& deltaTime);
	void UpdatePoseTransform(const int& boneIndex);
	
	Mat4 GetPoseMat() const;
};
