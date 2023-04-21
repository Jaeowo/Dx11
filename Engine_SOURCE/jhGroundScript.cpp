#include "jhGroundScript.h"
#include "jhCollider2D.h"
#include "jhPlayer.h"
#include "jhPlayerManager.h"
#include "jhComponent.h"
#include "jhPlayerManager.h"
#include "jhPlayerScript.h"

namespace jh
{
	GroundScript::GroundScript()
		:mCount(0)
	{
	}
	GroundScript::~GroundScript()
	{
	}
	void GroundScript::Initalize()
	{
	}
	void GroundScript::Update()
	{
	}
	void GroundScript::Render()
	{
	}
	void GroundScript::OnCollisionEnter(Collider2D* collider)
	{

		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());

		playerObj->SetIsGround(true);

		if (playerObj->GetPlayerState() == ePlayerState::Jump)
		{
			playerObj->SetPlayerState(ePlayerState::Idle);
			playerObj->SetCount(0);
		}
	

	
		//float fLen = fabs(collider->GetPosition().y - GetOwner()->GetComponent<Collider2D>()->GetPosition().y);
		//float fScale = collider->GetSize().y / 2.0f + GetOwner()->GetComponent<Collider2D>()->GetSize().y / 2.0f;


		//if (fLen < fScale)
		//{
		//	Vector3 playerPos = playerObj->GetPlayerPos();
		//	playerPos.y -= (fScale - fLen) - 1.0f;
		//	playerObj->SetPos(playerPos);
		//}
	
	}
	void GroundScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void GroundScript::OnCollisionExit(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());

		playerObj->SetIsGround(false);
	}
}