#include "jhGawkScript.h"
#include "jhGawk.h"
#include "jhPlayer.h"
#include "jhGeddyBullet.h"
#include "jhGeddyBulletEffect.h"
#include "jhObject.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"
#include "jhResources.h"

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

		std::shared_ptr<AudioClip> gawkflap = std::make_shared<AudioClip>();
		gawkflap->Load(L"..\\Resources\\Audio\\Gawk\\gawkFlap.wav");
		Resources::Insert<AudioClip>(L"GawkFlap", gawkflap);
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
				std::shared_ptr<AudioClip> gawkflap = Resources::Find<AudioClip>(L"GawkFlap");
				gawkflap->Play();
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

		GeddyBullet* geddyBulletObj = dynamic_cast<GeddyBullet*>(collider->GetOwner());

		if (geddyBulletObj)
		{

			if (mgawk->GetState() != eGawkState::UpsideDown)
			{
				mgawk->SetCount(0);
				mgawk->SetState(eGawkState::Hurt);

				std::shared_ptr<AudioClip> clip4 = Resources::Find<AudioClip>(L"Hit");
				clip4->Play();

				GeddyBulletEffect* geddybulleteffectobj = object::Instantiate<GeddyBulletEffect>(eLayerType::BackGround);
				geddybulleteffectobj->SetPosition(geddyBulletObj->GetPosition());
				geddyBulletObj->Death();
			}
			
		}
		
	}
	void GawkScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void GawkScript::OnCollisionExit(Collider2D* collider)
	{
	}
}