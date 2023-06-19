#include "jhAegisScript.h"
#include "jhPlayer.h"
#include "jhGeddyBullet.h"
#include "jhAegis.h"

namespace jh
{
	AegisScript::AegisScript()
		:Script()
	{

	}
	AegisScript::~AegisScript()
	{
	}
	void AegisScript::Initalize()
	{
		mAegis = dynamic_cast<Aegis*>(GetOwner());
	}
	void AegisScript::Update()
	{

	}
	void AegisScript::Render()
	{
	}
	void AegisScript::OnCollisionEnter(Collider2D* collider)
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
			mAegis->SetAegisState(eAegisState::Die);
			mAegis->SetCount(false);
		}

	}
	void AegisScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void AegisScript::OnCollisionExit(Collider2D* collider)
	{
	}
}