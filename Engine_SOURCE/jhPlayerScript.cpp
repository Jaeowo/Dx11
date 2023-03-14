#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhAnimator.h"

namespace jh
{
	PlayerScript::PlayerScript()
		:Script()
		, mPlayerState(ePlayerState::Idle)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
	}
	void PlayerScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

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
				Vector3 pos = tr->GetPosition();
				pos.y += 0.1f;
				tr->SetPosition(pos);
				mPlayerState = ePlayerState::Jump;
			}
		}

		if (mPlayerState == ePlayerState::Jump)
		{
			if (Input::GetKeyDown(eKeyCode::UP))
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
			Animator* animator = GetOwner()->GetComponent<Animator>();
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