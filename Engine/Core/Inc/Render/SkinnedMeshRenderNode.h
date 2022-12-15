#ifndef __SKINNEDMESHRENDERNODE_H__
#define __SKINNEDMESHRENDERNODE_H__

#include "MeshRenderNode.h"
#include "Animation/Skeleton.h"

WHITEBOX_BEGIN

class CSkinnedMeshRenderNode : public CMeshRenderNode
{
public:
	virtual void	Refresh() override;
	void			ApplySkinningPose( const CPose& skinningPose );
	void			ApplySkinningPose( const float* boneMatrices, size_t boneCount );


private:
	void*	m_skinMatricesBufferId;
};

DEFINE_SMART_PTR(CSkinnedMeshRenderNode)

WHITEBOX_END

#endif
