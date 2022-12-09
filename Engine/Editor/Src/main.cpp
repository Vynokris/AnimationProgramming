
#include "Engine.h"
#include "Simulation.h"
#include "Animation\Animation.h"
#include "Animation\Skeleton.h"
#include "GlobalVariables.h"
#include "Application.h"
#include "Render\SkinnedMeshRenderNode.h"

using namespace WhiteBox;

class CSimulation : public ISimulation
{
public:
	float tim = 0;
	float blendWeight = 0;
	float normalizedTime = 0;

	virtual ~CSimulation()
	{

	}

	virtual void Init() override
	{

		Transform t;
		GetAnimLocalBoneTransform("ThirdPersonWalk.anim", 10, 0, t.position.x, t.position.y, t.position.z, t.rotation.w, t.rotation.x, t.rotation.y, t.rotation.z);
	
		//int x = 2;
	}

	virtual void Update( float frameTime ) override
	{
		CAnimationPtr	pAnim1 = "ThirdPersonWalk.anim";
		CAnimationPtr	pAnim2 = "ThirdPersonRun.anim";

		CSkeletonPtr	pCharacterSkel = gVars->pApplication->pCharacterSkel;
		CSkinnedMeshRenderNodePtr pCharacterRenderNode = gVars->pApplication->pCharacterRenderNode;

		{
			size_t boneCount = pCharacterSkel->GetBones().size();





			auto itBoneInfo = pCharacterSkel->GetBoneNameToIndexMap().FindElement("spine_03");


			CPose pose;
			pose.m_boneTransforms.resize(boneCount);
			pose.Zero();

			{
				float factor = 1.f;


				/*	tim = 4.95f;*/
				if (tim < 4.0f)
				{
					blendWeight = 0;
				}
				else if (tim < 6.0f)
				{
					blendWeight = (tim - 4.0f) / 2.0f;
				}
				else if (tim < 10.0f)
				{

					blendWeight = 1.0f;
				}
				else if (tim < 12.0f)
				{
					blendWeight = 1.0f - (tim - 10.0f) / 2.0f;
				}
				else
				{
					tim = 0.0f;
				}
				tim += frameTime * factor;


				/*blendWeight = 1.0f;*/

				// 		normalizedTime = 0.60f;

				float length = (1.0f - blendWeight) * pAnim1->m_length + blendWeight * pAnim2->m_length;
				float speed = 1.0f / length;
				normalizedTime += speed * frameTime * factor;
			}



			{
				pose.Zero();
				/*blendWeight = 1.0f;*/

				// 		normalizedTime = 0.60f;
				if (true)
				{
					float length = (1.0f - blendWeight) * pAnim1->m_length + blendWeight * pAnim2->m_length;
					float speed = 1.0f / length;

					float w = 0.0f;

					pAnim1->AccumulateSamplePose((normalizedTime)* pAnim1->m_length, 1.0f - blendWeight, pose, w);
					pAnim2->AccumulateSamplePose((normalizedTime)* pAnim2->m_length, blendWeight, pose, w);

					//pAnim1->AccumulateSamplePose(normalizedTime * pAnim1->m_length, 1.0f - blendWeight, pose, w);
					//pAnim2->AccumulateSamplePose(normalizedTime * pAnim2->m_length, blendWeight, pose, w);

					pose.Normalize(w);
				}

				pCharacterSkel->ConvertFromBindToLocalSpace(pose);
				pCharacterSkel->ComputeGlobalPose(pose, pose);

				pCharacterSkel->ComputeSkinningPose(pose, pose);

				{
					Matrix44* matrices = new Matrix44[64];
					for (int i = 0; i < 64; ++i)
					{
						Matrix34 m;
						m.FromTransform(pose.m_boneTransforms[i]);

						matrices[i] = Matrix44(m);
					}

					SetSkinningPose((float*)matrices, 64);

					delete[] matrices;
				}

				//pCharacterRenderNode->ApplySkinningPose(pose);


				
			}
		}
	}
};


int main(int argc, char **argv)
{
	CSimulation simulation;
	Run(&simulation, 1600, 800);

	return 0;
}

