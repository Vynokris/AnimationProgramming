#include "Animation/Bone.h"

void Bone::UpdateChildrenTransform(const Mat4 & parentMat)
{
	const Mat4 curMat = parentMat * transform.GetLocalMat();
	for (Bone* child : children)
	{
		child->transform.SetWorldMat(curMat);
		child->UpdateChildrenTransform(curMat);
	}
}