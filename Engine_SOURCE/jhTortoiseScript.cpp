#include "jhTortoiseScript.h"
#include "jhPlayer.h"
#include "jhTortoise.h"
#include "jhGeddyBullet.h"
#include "jhPlayerAttackCol.h"
#include "jhTortoiseMask.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"
#include "jhResources.h"
#include "jhObject.h"
#include "jhGeddyBulletEffect.h"

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

		std::shared_ptr<AudioClip> bulletimpact = std::make_shared<AudioClip>();
		bulletimpact->Load(L"..\\Resources\\Audio\\bulletImpact1.wav");
		Resources::Insert<AudioClip>(L"BulletImpact", bulletimpact);



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
					std::shared_ptr<AudioClip> bulletimpact = Resources::Find<AudioClip>(L"BulletImpact");
					bulletimpact->Play();
					mtortoise->SetPlayerState(eTortoiseState::RemoveFlyMask);
				}
				else
				{
					mtortoise->SetAniCheck(false);
					std::shared_ptr<AudioClip> bulletimpact = Resources::Find<AudioClip>(L"BulletImpact");
					bulletimpact->Play();
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

				std::shared_ptr<AudioClip> clip4 = Resources::Find<AudioClip>(L"Hit");
				clip4->Play();

				GeddyBulletEffect* geddybulleteffectobj = object::Instantiate<GeddyBulletEffect>(eLayerType::BackGround);
				geddybulleteffectobj->SetPosition(geddyBulletObj->GetPosition());
				geddyBulletObj->Death();
			
			}
			else if (mtortoise->GetPlayerState() == eTortoiseState::MaskMove ||
					mtortoise->GetPlayerState() == eTortoiseState::MaskFly)
			{
				std::shared_ptr<AudioClip> bulletimpact = Resources::Find<AudioClip>(L"BulletImpact");
				bulletimpact->Play();

				GeddyBulletEffect* geddybulleteffectobj = object::Instantiate<GeddyBulletEffect>(eLayerType::BackGround);
				geddybulleteffectobj->SetPosition(geddyBulletObj->GetPosition());
				geddyBulletObj->Death();
			}
			else
			{
	
				GeddyBulletEffect* geddybulleteffectobj = object::Instantiate<GeddyBulletEffect>(eLayerType::BackGround);
				geddybulleteffectobj->SetPosition(geddyBulletObj->GetPosition());
				geddyBulletObj->Death();

			}
			if (mtortoise->GetPlayerState() == eTortoiseState::Fly)
			{
				int tortoisehpCheck = (mtortoise->GetHp() - 1);
				mtortoise->SetHp(tortoisehpCheck);

				mtortoise->SetAniCheck(false);
				mtortoise->SetPlayerState(eTortoiseState::FlyHit);

				std::shared_ptr<AudioClip> clip4 = Resources::Find<AudioClip>(L"Hit");
				clip4->Play();

				GeddyBulletEffect* geddybulleteffectobj = object::Instantiate<GeddyBulletEffect>(eLayerType::BackGround);
				geddybulleteffectobj->SetPosition(geddyBulletObj->GetPosition());
				geddyBulletObj->Death();
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