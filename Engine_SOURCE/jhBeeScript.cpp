#include "jhBeeScript.h"
#include "jhBee.h"
#include "jhGeddyBullet.h"
#include "jhPlayer.h"
#include "jhGeddyBulletEffect.h"
#include "jhObject.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"
#include "jhResources.h"

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

		GeddyBullet* geddyBulletObj = dynamic_cast<GeddyBullet*>(collider->GetOwner());
		if (geddyBulletObj)
		{
			mBee->SetBeeState(eBeeState::Hit);
			mBee->SetCount(false);

			std::shared_ptr<AudioClip> clip4 = Resources::Find<AudioClip>(L"Hit");
			clip4->Play();

			GeddyBulletEffect* geddybulleteffectobj = object::Instantiate<GeddyBulletEffect>(eLayerType::BackGround);
			geddybulleteffectobj->SetPosition(geddyBulletObj->GetPosition());
			geddyBulletObj->Death();
		}

	}
	void BeeScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void BeeScript::OnCollisionExit(Collider2D* collider)
	{
	}
}