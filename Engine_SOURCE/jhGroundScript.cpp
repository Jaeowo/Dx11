#include "jhGroundScript.h"
#include "jhCollider2D.h"
#include "jhPlayer.h"
#include "jhPlayerManager.h"
#include "jhComponent.h"
#include "jhPlayerScript.h"
#include "jhGeddy.h"
#include "jhGeddyScript.h"
#include "jhGawk.h"

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
		}
	
		Geddy* geddyObj = dynamic_cast<Geddy*>(collider->GetOwner());

		if (geddyObj)
		{
			
			geddyObj->SetIsGround(false);
		
		}
	
	}
}