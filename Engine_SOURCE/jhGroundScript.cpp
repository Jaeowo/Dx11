#include "jhGroundScript.h"
#include "jhCollider2D.h"
#include "jhPlayer.h"
#include "jhPlayerManager.h"
#include "jhComponent.h"
#include "jhPlayerScript.h"
#include "jhGeddy.h"
#include "jhGeddyScript.h"
#include "jhGawk.h"
#include "jhCoin.h"
#include "jhCoinScript.h"
#include "jhTortoiseMask.h"

namespace jh
{
	GroundScript::GroundScript()
		:mCount(0)
	{
	}
	GroundScript::~GroundScript()
	{
	}
	void GroundScript::Initalize()
	{
	}
	void GroundScript::Update()
	{
	}
	void GroundScript::Render()
	{
	}
	void GroundScript::OnCollisionEnter(Collider2D* collider)
	{

		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());

		if (playerObj)
		{
			playerObj->SetIsGround(true);

			if (playerObj->GetPlayerState() == ePlayerState::Fall)
			{
				playerObj->SetPlayerState(ePlayerState::Idle);
				playerObj->SetCount(0);
			}

			if (playerObj->GetIsFlyDown() == true)
			{
				playerObj->SetPlayerState(ePlayerState::Idle);
				playerObj->SetCount(0);
			}

			// adjust the player's position to be just above the ground
			Vector3 playerPos = playerObj->GetPlayerPos();
			Transform* groundTransform = this->GetOwner()->GetComponent<Transform>();
			const float PLAYER_COLLIDER_HEIGHT = 1.0f;  // replace with the actual value
			float groundTop = groundTransform->GetPosition().y + (groundTransform->GetScale().y / 2);
			playerPos.y = groundTop + PLAYER_COLLIDER_HEIGHT / 2;
			playerObj->SetPlayerPos(playerPos);

			// set the vertical speed to 0
			//playerObj->SetVelocityZero(true);
		}
		else
		{
			Geddy* geddyObj = dynamic_cast<Geddy*>(collider->GetOwner());

			if (geddyObj)
			{
				geddyObj->SetIsGround(true);

				if (geddyObj->GetGeddyState() == eGeddyState::Falling)
				{
					geddyObj->SetGeddyState(eGeddyState::Idle);
					geddyObj->SetCount(0);
				}
			}
		}

		Coin* coinObj = dynamic_cast<Coin*>(collider->GetOwner());

		if (coinObj)
		{
			coinObj->SetGround(true);
		}

		TortoiseMask* maskObj = dynamic_cast<TortoiseMask*>(collider->GetOwner());

		if(maskObj)
		{
			maskObj->SetGround(true);
		}


	}
	void GroundScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void GroundScript::OnCollisionExit(Collider2D* collider)
	{

		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());

		if (playerObj)
		{
			if (playerObj->GetIsFly() == false)
			{
				playerObj->SetIsGround(false);
			}

			playerObj->SetVelocityZero(false);
		}

		Geddy* geddyObj = dynamic_cast<Geddy*>(collider->GetOwner());

		if (geddyObj)
		{

			geddyObj->SetIsGround(false);

		}

	}
}