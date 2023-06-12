#include "jhWallScript.h"
#include "jhPlayer.h"
#include "jhCoin.h"

namespace jh
{
	WallScript::WallScript()
		:mCount(0)
	{
	}
	WallScript::~WallScript()
	{
	}
	void WallScript::Initalize()
	{
	}
	void WallScript::Update()
	{
	}
	void WallScript::Render()
	{
	}
	void WallScript::HandleWallCollision(Collider2D* collider)
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

	void WallScript::OnCollisionEnter(Collider2D* collider)
	{
		HandleWallCollision(collider);
	}

	void WallScript::OnCollisionStay(Collider2D* collider)
	{
		HandleWallCollision(collider);
	}

	void WallScript::OnCollisionExit(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());
		if (playerObj)
		{
			playerObj->SetVelocityZero(false);
		}
	}
}