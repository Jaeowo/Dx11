#include "jhStoneDoorScript.h"
#include "jhPlayer.h"

namespace jh
{
	StoneDoorScript::StoneDoorScript()
		:mCount(0)
	{
	}
	StoneDoorScript::~StoneDoorScript()
	{
	}
	void StoneDoorScript::Initalize()
	{
	}
	void StoneDoorScript::Update()
	{
	}
	void StoneDoorScript::Render()
	{
	}

	void StoneDoorScript::OnCollisionEnter(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());
		if (playerObj)
		{
			Vector3 previousPos = playerObj->GetPreviousPos();
			playerObj->getTransform()->SetPosition(previousPos);
			playerObj->SetPlayerPos(previousPos);

			playerObj->SetVelocityZero(true);

		}
	}

	void StoneDoorScript::OnCollisionStay(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());
		if (playerObj)
		{
			Vector3 previousPos = playerObj->GetPreviousPos();
			playerObj->getTransform()->SetPosition(previousPos);
			playerObj->SetPlayerPos(previousPos);

			playerObj->SetVelocityZero(true);

		}
	}

	void StoneDoorScript::OnCollisionExit(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());
		if (playerObj)
		{
			playerObj->SetVelocityZero(false);
		}
	}
}