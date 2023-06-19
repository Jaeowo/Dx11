#include "jhButtonScript.h"
#include "jhPlayer.h"
#include "jhGeddy.h"
#include "jhButton.h"

namespace jh
{
	ButtonScript::ButtonScript()
		:mCount(0)
	{
	}
	ButtonScript::~ButtonScript()
	{
	}
	void ButtonScript::Initalize()
	{
		mbutton = dynamic_cast<Button*>(GetOwner());
	}
	void ButtonScript::Update()
	{
	}
	void ButtonScript::Render()
	{
	}

	void ButtonScript::OnCollisionEnter(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());

		if (playerObj)
		{
			playerObj->SetIsGround(true);

			if (playerObj->GetPlayerState() == ePlayerState::Fall)
			{
				//playerObj->SetPlayerState(ePlayerState::Idle);
				//playerObj->SetCount(0);
			}

			if (playerObj->GetIsFlyDown() == true)
			{
				playerObj->SetPlayerState(ePlayerState::Idle);
				playerObj->SetCount(0);
			}

			Vector3 playerPos = playerObj->GetPlayerPos();
			Transform* groundTransform = this->GetOwner()->GetComponent<Transform>();
			const float PLAYER_COLLIDER_HEIGHT = 1.0f; 
			float groundTop = groundTransform->GetPosition().y + (groundTransform->GetScale().y / 2);
			playerPos.y = groundTop + PLAYER_COLLIDER_HEIGHT / 2;

			
			if (playerObj->GetPlayerState() == ePlayerState::Fall)
			{
				if (mCount == 0)
				{
					mbutton->SetPressTrigger(true);
					mbutton->SetCount(false);
					mCount = 1;
				}
		
			}
		}

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

	void ButtonScript::OnCollisionStay(Collider2D* collider)
	{
	
	}

	void ButtonScript::OnCollisionExit(Collider2D* collider)
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