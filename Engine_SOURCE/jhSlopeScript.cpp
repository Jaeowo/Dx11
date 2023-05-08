#include "jhSlopeScript.h"
#include "jhPlayer.h"
#include "jhGeddy.h"

namespace jh
{
	SlopeScript::SlopeScript()
		:mCount(0)
	{
	}
	SlopeScript::~SlopeScript()
	{
	}
	void SlopeScript::Initalize()
	{
	}
	void SlopeScript::Update()
	{
	}
	void SlopeScript::Render()
	{
	}
	void SlopeScript::OnCollisionEnter(Collider2D* collider)
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



	}
	void SlopeScript::OnCollisionStay(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());

		if (playerObj->GetPlayerRotation().y >= 180.0f)
		{
			playerObj->SetPlayerRotation(Vector3(0.0f, 180.0f, 310.0f));
		}
		else
		{
			playerObj->SetPlayerRotation(Vector3(0.0f, 0.0f, 310.0f));
		}
	}
	void SlopeScript::OnCollisionExit(Collider2D* collider)
	{

		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());

		if (playerObj)
		{
			if (playerObj->GetIsFly() == false)
			{
				playerObj->SetIsGround(false);
			}
			playerObj->SetPlayerRotation(Vector3(0.0f, 0.0f, 0.0f));
		}

		Geddy* geddyObj = dynamic_cast<Geddy*>(collider->GetOwner());

		if (geddyObj)
		{

			geddyObj->SetIsGround(false);

		}

	}
}