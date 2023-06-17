#include "jhGawkScript.h"
#include "jhGawk.h"
#include "jhPlayer.h"
#include "jhGeddyBullet.h"

namespace jh
{
	GawkScript::GawkScript()
		:Script()
	{

	}
	GawkScript::~GawkScript()
	{
	}
	void GawkScript::Initalize()
	{
		mgawk = dynamic_cast<Gawk*>(GetOwner());
	}
	void GawkScript::Update()
	{

	}
	void GawkScript::Render()
	{
	}
	void GawkScript::OnCollisionEnter(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());

		if (playerObj)
		{
			if (mgawk->GetState() == eGawkState::UpsideDown)
			{
				mgawk->SetState(eGawkState::UpsideDowntoFly);
				mgawk->SetCount(0);
			}
			else
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
		}

		GeddyBullet* geddyBulletObj = dynamic_cast<GeddyBullet*>(collider->GetOwner());
		if (geddyBulletObj)
		{
			mgawk->SetCount(0);
			mgawk->SetState(eGawkState::Hurt);
		}
		
	}
	void GawkScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void GawkScript::OnCollisionExit(Collider2D* collider)
	{
	}
}