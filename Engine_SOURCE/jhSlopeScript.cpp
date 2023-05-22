#include "jhSlopeScript.h"
#include "jhPlayer.h"
#include "jhGeddy.h"
#include "jhSlope.h"

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
		Geddy* geddyObj = dynamic_cast<Geddy*>(collider->GetOwner());
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





		if (this->mslope != nullptr)
		{
			if (this->mslope->GetLeftUP() == true)
			{
				if (playerObj)
				{
					playerObj->SetIsLeftSlope(true);
				}
			}
			else if (this->mslope->GetRightUp() == true)
			{
				if (playerObj)
				{
					playerObj->SetIsRightSlope(true);
				}
			}
		}

	}
	void SlopeScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void SlopeScript::OnCollisionExit(Collider2D* collider)
	{

		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());

		if (playerObj)
		{
			if (playerObj->GetIsFly() == false)
			{
				playerObj->SetIsGround(false);
				playerObj->SetIsLeftSlope(false);
				playerObj->SetIsRightSlope(false);
			}
		}

		Geddy* geddyObj = dynamic_cast<Geddy*>(collider->GetOwner());

		if (geddyObj)
		{

			geddyObj->SetIsGround(false);

		}

	}
}