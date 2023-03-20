#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhAnimator.h"
#include "jhPlayerManager.h"
#include "jhPlayer.h"

namespace jh
{
	PlayerScript::PlayerScript()
		:Script()
		, mPlayerState(ePlayerState::Idle)
		, mbGround(false)
		, mbCarrying(false)
		, mGravity(0.2f)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initalize()
	{


	}
	void PlayerScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		if (mbGround == true && mPlayerState != ePlayerState::Fly)
		{
			Vector3 pos = tr->GetPosition();
			pos.y -= mGravity * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (mPlayerState == ePlayerState::Idle)
		{

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				Vector3 pos = tr->GetPosition();
				pos.x += 0.5f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			if (Input::GetKey(eKeyCode::LEFT))
			{
				Vector3 pos = tr->GetPosition();
				pos.x -= 0.5f * Time::DeltaTime();
				tr->SetPosition(pos);
			}

			if (Input::GetKeyDown(eKeyCode::UP))
			{
				
				mPlayerState = ePlayerState::Jump;
			}
		}

		if (mPlayerState == ePlayerState::Jump)
		{
			if (Input::GetKey(eKeyCode::UP))
			{
			/*	float MaxHeight = 0.3f;
				float JumpPower = 1.0f;
				Vector3 pos = tr->GetPosition();
				pos.y += JumpPower * 0.3f * Time::DeltaTime();
				if (pos.y >= MaxHeight)
				{
					pos.y -= mGravity * Time::DeltaTime();
					JumpPower = 0.0f;
				}
				tr->SetPosition(pos);*/

				Vector3 pos = tr->GetPosition();
				pos.y +=  0.3f * Time::DeltaTime();
				tr->SetPosition(pos);
			}


			if (Input::GetKeyUp(eKeyCode::UP))
			{
				mPlayerState = ePlayerState::Fly;
			}
		}

		if (mPlayerState == ePlayerState::Fly)
		{
			if (Input::GetKey(eKeyCode::RIGHT))
			{
				Vector3 pos = tr->GetPosition();
				pos.x += 0.5f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			if (Input::GetKey(eKeyCode::LEFT))
			{
				Vector3 pos = tr->GetPosition();
				pos.x -= 0.5f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			if (Input::GetKey(eKeyCode::DOWN))
			{
				Vector3 pos = tr->GetPosition();
				pos.y -= 0.5f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			if (Input::GetKey(eKeyCode::UP))
			{
				Vector3 pos = tr->GetPosition();
				pos.y += 0.5f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			//Animator* animator = GetOwner()->GetComponent<Animator>();
		}
		
	}
	void PlayerScript::Render()
	{
	}
	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{
	}
}