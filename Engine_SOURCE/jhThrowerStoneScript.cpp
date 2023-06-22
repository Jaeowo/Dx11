#include "jhThrowerStoneScript.h"
#include "jhPlayer.h"
#include "jhAegisBullet.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"
#include "jhResources.h"
#include "jhThrowerStone.h"

namespace jh
{
	ThrowerStoneScript::ThrowerStoneScript()
		:Script()
	{

	}
	ThrowerStoneScript::~ThrowerStoneScript()
	{
	}
	void ThrowerStoneScript::Initalize()
	{
		mThrowerStone = dynamic_cast<ThrowerStone*>(GetOwner());
	}
	void ThrowerStoneScript::Update()
	{

	}
	void ThrowerStoneScript::Render()
	{
	}
	void ThrowerStoneScript::OnCollisionEnter(Collider2D* collider)
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
				std::shared_ptr<AudioClip> clip4 = Resources::Find<AudioClip>(L"Hit");
				clip4->Play();
			}
			else
			{
				playerObj->SetCount(0);
				playerObj->SetPlayerState(ePlayerState::Hurt);
				std::shared_ptr<AudioClip> clip4 = Resources::Find<AudioClip>(L"Hit");
				clip4->Play();
			}


		}

	}
	void ThrowerStoneScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void ThrowerStoneScript::OnCollisionExit(Collider2D* collider)
	{
	}
}