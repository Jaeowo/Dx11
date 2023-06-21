#include "jhBeeScript.h"
#include "jhBee.h"
#include "jhGeddyBullet.h"
#include "jhPlayer.h"

namespace jh
{
	BeeScript::BeeScript()
		:Script()
	{

	}
	BeeScript::~BeeScript()
	{
	}
	void BeeScript::Initalize()
	{
		mBee = dynamic_cast<Bee*>(GetOwner());
	}
	void BeeScript::Update()
	{

	}
	void BeeScript::Render()
	{
	}
	void BeeScript::OnCollisionEnter(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());

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

		GeddyBullet* geddyBulletObj = dynamic_cast<GeddyBullet*>(collider->GetOwner());
		if (geddyBulletObj)
		{

			//mBee->SetBeeState(eBeeState::Hit);
			/*int hpCheck = (mBee->GetHp() - 1);
			mBee->SetHp(hpCheck);*/
			mBee->SetCount(false);
		}

	}
	void BeeScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void BeeScript::OnCollisionExit(Collider2D* collider)
	{
	}
}