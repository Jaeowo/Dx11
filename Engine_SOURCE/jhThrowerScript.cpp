#include "jhThrowerScript.h"
#include "jhPlayer.h"
#include "jhGeddyBullet.h"
#include "jhThrower.h"

namespace jh
{
	ThrowerScript::ThrowerScript()
		:Script()
	{

	}
	ThrowerScript::~ThrowerScript()
	{
	}
	void ThrowerScript::Initalize()
	{
		mThrower = dynamic_cast<Thrower*>(GetOwner());
	}
	void ThrowerScript::Update()
	{

	}
	void ThrowerScript::Render()
	{
	}
	void ThrowerScript::OnCollisionEnter(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());

		if (playerObj)
		{
			if (mThrower->GetThrowerState() == eThrowerState::Idle)
			{
				mThrower->SetCount(false);
				mThrower->SetThrowerState(eThrowerState::Follow);
			}


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

		GeddyBullet* geddyBulletObj = dynamic_cast<GeddyBullet*>(collider->GetOwner());
		if (geddyBulletObj)
		{
			if (mThrower->GetThrowerState() == eThrowerState::Idle)
			{
				return;
			}
			mThrower->SetThrowerState(eThrowerState::Hurt);
			mThrower->SetCount(false);

		}

	}
	void ThrowerScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void ThrowerScript::OnCollisionExit(Collider2D* collider)
	{
	}
}