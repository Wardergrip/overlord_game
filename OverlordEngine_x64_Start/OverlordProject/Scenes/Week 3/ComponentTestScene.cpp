#include "stdafx.h"
#include "ComponentTestScene.h"

#include "Prefabs/SpherePrefab.h"

void ComponentTestScene::Initialize()
{
	auto& pPhysx = PxGetPhysics();
	auto pBouncyMaterial = pPhysx.createMaterial(.5f, .5f, 1.f);
	
	//GROUND PLANE
	GameSceneExt::CreatePhysXGroundPlane(*this, pBouncyMaterial);

	//SPhere Red (Group 0)
	{
		auto pSphere = new SpherePrefab(1, 10, XMFLOAT4{ Colors::Red });
		AddChild(pSphere);

		pSphere->GetTransform()->Translate(0, 30, 0);
		auto rb = pSphere->AddComponent(new RigidBodyComponent(false));
		rb->AddCollider(PxSphereGeometry{ 1.f }, *pBouncyMaterial);
		rb->SetCollisionGroup(CollisionGroup::Group0);
	}

	//SPhere Green (Group 1)
	{
		auto pSphere = new SpherePrefab(1, 10, XMFLOAT4{ Colors::Green });
		AddChild(pSphere);

		pSphere->GetTransform()->Translate(0, 15, 0);
		auto rb = pSphere->AddComponent(new RigidBodyComponent(false));
		rb->AddCollider(PxSphereGeometry{ 1.f }, *pBouncyMaterial);
		rb->SetCollisionGroup(CollisionGroup::Group1);
		rb->SetConstraint(RigidBodyConstraint::TransX | RigidBodyConstraint::TransZ,false);
	}

	//SPhere Blue (Group 2)
	{
		auto pSphere = new SpherePrefab(1, 10, XMFLOAT4{ Colors::Blue });
		AddChild(pSphere);

		pSphere->GetTransform()->Translate(0, 5, 0);
		auto rb = pSphere->AddComponent(new RigidBodyComponent(false));
		rb->AddCollider(PxSphereGeometry{ 1.f }, *pBouncyMaterial);
		rb->SetCollisionGroup(CollisionGroup::Group2);
	}
}
