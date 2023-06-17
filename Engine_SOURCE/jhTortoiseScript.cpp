#include "jhTortoiseScript.h"
#include "jhPlayer.h"
#include "jhTortoise.h"
#include "jhGeddyBullet.h"
#include "jhPlayerAttackCol.h"
#include "jhTortoiseMask.h"

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
			if (playerObj->GetIsInvincible())  
			{
				return;
			}

			int hpCheck = (playerObj->GetHp() - 1);
			playerObj->SetHp(hpCheck);

			playerObj->SetInvincibleTimer(0.0f);
			playerObj->SetIsInvincible(true);

			if (playerObj->GetIsFly())
			{
				playerObj->SetCount(0);
				playerObj->SetPlayerState(ePlayerState::FlyHurt);
			}
			else
			{
				playerObj->SetCount(0);
				playerObj->SetPlayerState(ePlayerState::Hurt);
			}
		}

		if (attackcol)
		{
			if (mtortoise->GetPlayerState() == eTortoiseState::MaskSpawnWing)
			{
				return;
			}

			if (mtortoise->GetPlayerState() == eTortoiseState::MaskMove ||
				mtortoise->GetPlayerState() == eTortoiseState::MaskFly)
			{
				if (mtortoise->GetPlayerState() == eTortoiseState::MaskFly)
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
		}

		GeddyBullet* geddyBulletObj = dynamic_cast<GeddyBullet*>(collider->GetOwner());
		if (geddyBulletObj)
		{

			if (mtortoise->GetPlayerState() == eTortoiseState::MaskSpawnWing)
			{
				return;
			}

			if (mtortoise->GetEventOn() == true)
			{
				return;
			}
			if (mtortoise->GetPlayerState() == eTortoiseState::Move )
			{
				int tortoisehpCheck = (mtortoise->GetHp() - 1);
				mtortoise->SetHp(tortoisehpCheck);

				mtortoise->SetAniCheck(false);
				mtortoise->SetPlayerState(eTortoiseState::Hit);
			
			}
			if (mtortoise->GetPlayerState() == eTortoiseState::Fly)
			{
				int tortoisehpCheck = (mtortoise->GetHp() - 1);
				mtortoise->SetHp(tortoisehpCheck);

				mtortoise->SetAniCheck(false);
				mtortoise->SetPlayerState(eTortoiseState::FlyHit);
			}
			
		
		}

		TortoiseMask* tortoisemaskObj = dynamic_cast<TortoiseMask*>(collider->GetOwner());
		if (tortoisemaskObj)
		{
			if (mtortoise->GetPlayerState() == eTortoiseState::Move)
			{
				mtortoise->SetAniCheck(false);
				mtortoise->SetPlayerState(eTortoiseState::EquipMask);
			}
			
			if (mtortoise->GetPlayerState() == eTortoiseState::Fly)
			{
				mtortoise->SetAniCheck(false);
				mtortoise->SetPlayerState(eTortoiseState::FlyEquipMask);
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