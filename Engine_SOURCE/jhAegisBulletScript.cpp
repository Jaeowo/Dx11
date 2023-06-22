#include "jhAegisBulletScript.h"
#include "jhPlayer.h"
#include "jhAegisBullet.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"
#include "jhResources.h"

namespace jh
{
	AegisBulletScript::AegisBulletScript()
		:Script()
	{

	}
	AegisBulletScript::~AegisBulletScript()
	{
	}
	void AegisBulletScript::Initalize()
	{
		mAegisBullet = dynamic_cast<AegisBullet*>(GetOwner());
	}
	void AegisBulletScript::Update()
	{

	}
	void AegisBulletScript::Render()
	{
	}
	void AegisBulletScript::OnCollisionEnter(Collider2D* collider)
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
	void AegisBulletScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void AegisBulletScript::OnCollisionExit(Collider2D* collider)
	{
	}
}