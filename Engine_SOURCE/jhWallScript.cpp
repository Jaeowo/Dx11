#include "jhWallScript.h"
#include "jhPlayer.h"
#include "jhCoin.h"
#include "jhTortoiseMask.h"
#include "jhTortoise.h"
#include "jhGeddyBullet.h"
#include "jhGeddyBulletEffect.h"
#include "jhObject.h"
#include "jhThrower.h"
#include "jhTortoiseBullet.h"
#include "jhAegisBullet.h"
#include "jhThrowerStone.h"

namespace jh
{
	WallScript::WallScript()
		:mCount(0)
	{
	}
	WallScript::~WallScript()
	{
	}
	void WallScript::Initalize()
	{
	}
	void WallScript::Update()
	{
	}
	void WallScript::Render()
	{
	}
	void WallScript::HandleWallCollision(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());
		if (playerObj)
		{
			Vector3 previousPos = playerObj->GetPreviousPos();
			playerObj->getTransform()->SetPosition(previousPos);
			playerObj->SetPlayerPos(previousPos);

			playerObj->SetVelocityZero(true);
			
		}

		TortoiseMask* tortoisemaskObj = dynamic_cast<TortoiseMask*>(collider->GetOwner());
		if (tortoisemaskObj)
		{
			tortoisemaskObj->ReverseDirection();
		}
		Tortoise* tortoiseObj = dynamic_cast<Tortoise*>(collider->GetOwner());
		if (tortoiseObj && tortoiseObj->GetIgnoreCollisionTime() <= 0.0f) 
		{
			if (tortoiseObj->GetPlayerState() == eTortoiseState::MaskMove ||
				tortoiseObj->GetPlayerState() == eTortoiseState::MaskShoot)
			{
				tortoiseObj->SetPlayerState(eTortoiseState::MaskTurn);
			}
			if (tortoiseObj->GetPlayerState() == eTortoiseState::Move) 
			{
				tortoiseObj->SetPlayerState(eTortoiseState::Turn);
			}
		}

		GeddyBullet* geddybulletObj = dynamic_cast<GeddyBullet*>(collider->GetOwner());

		if (geddybulletObj)
		{
			GeddyBulletEffect* geddybulleteffectobj = object::Instantiate<GeddyBulletEffect>(eLayerType::BackGround);
			geddybulleteffectobj->SetPosition(geddybulletObj->GetPosition());
			geddybulletObj->Death();
		}

		Thrower* throwerObj = dynamic_cast<Thrower*>(collider->GetOwner());
		if (throwerObj)
		{
			if (throwerObj->GetThrowerState() == eThrowerState::Follow)
			{
				Vector3 previousPos = throwerObj->GetPreviousPos();
				throwerObj->SetPosition(previousPos);
			}
			

		}


	}

	void WallScript::OnCollisionEnter(Collider2D* collider)
	{
		HandleWallCollision(collider);

		TortoiseBullet* tortoisebulletobj = dynamic_cast<TortoiseBullet*>(collider->GetOwner());
		if (tortoisebulletobj)
		{
			tortoisebulletobj->Death();
		}

		AegisBullet* aegisbulletobj = dynamic_cast<AegisBullet*>(collider->GetOwner());
		if (aegisbulletobj)
		{
			aegisbulletobj->Death();
		}

		ThrowerStone* throwerstoneobj = dynamic_cast<ThrowerStone*>(collider->GetOwner());
		if (throwerstoneobj)
		{
			throwerstoneobj->Death();
		}
	}

	void WallScript::OnCollisionStay(Collider2D* collider)
	{
		HandleWallCollision(collider);
	}

	void WallScript::OnCollisionExit(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());
		if (playerObj)
		{
			playerObj->SetVelocityZero(false);
		}
		

		Thrower* throwerObj = dynamic_cast<Thrower*>(collider->GetOwner());
		if (throwerObj)
		{
			
		}
	}
}