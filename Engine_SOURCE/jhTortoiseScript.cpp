#include "jhTortoiseScript.h"
#include "jhPlayer.h"
#include "jhTortoise.h"
#include "jhGeddyBullet.h"
#include "jhPlayerAttackCol.h"

namespace jh
{
	TortoiseScript::TortoiseScript()
		:Script()
	{

	}
	TortoiseScript::~TortoiseScript()
	{
	}
	void TortoiseScript::Initalize()
	{
		mtortoise = dynamic_cast<Tortoise*>(GetOwner());
	}
	void TortoiseScript::Update()
	{

	}
	void TortoiseScript::Render()
	{
	}
	void TortoiseScript::OnCollisionEnter(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());
		PlayerAttackCol* attackcol = dynamic_cast<PlayerAttackCol*>(collider->GetOwner());

		if (playerObj)
		{
			playerObj->SetCount(0);
			playerObj->SetHurt(true);
		}

		if (attackcol)
		{
			if (mtortoise->GetIsFlying() == true)
			{
				mtortoise->SetAniCheck(false);
				mtortoise->SetPlayerState(eTortoiseState::RemoveFlyMask);
			}
			else
			{
				mtortoise->SetAniCheck(false);
				mtortoise->SetPlayerState(eTortoiseState::RemoveMask);
			}
			
		}

		GeddyBullet* geddyBulletObj = dynamic_cast<GeddyBullet*>(collider->GetOwner());
		if (geddyBulletObj)
		{
			if (mtortoise->GetMaskOn() == false)
			{
				mtortoise->SetAniCheck(false);
				mtortoise->SetPlayerState(eTortoiseState::Hit);
			}
			else
			{
			}
		
		}
	}
	void TortoiseScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void TortoiseScript::OnCollisionExit(Collider2D* collider)
	{
	}
}