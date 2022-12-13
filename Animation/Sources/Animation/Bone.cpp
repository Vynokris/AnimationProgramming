#include "Animation/Bone.h"

void Bone::UpdateChildrenTransform(const Mat4 & parentMat) const
{
	const Mat4 curMat = transform.GetLocalMat() * parentMat;
	for (Bone* child : children)
	{
		child->transform.SetWorldMat(curMat);
		child->UpdateChildrenTransform(curMat);
	}
}
