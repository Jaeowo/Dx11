#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"

namespace jh
{
	PlayerScript::PlayerScript()
		:Script()
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
		/*Transform* tr = GetOwner()->GetComponent<Transform>();

			Vector3 pos = tr->GetPosition();

			if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
			{
				pos.x += 3.0f * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
			{
				pos.x -= 3.0f * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
			{
				pos.y += 3.0f * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
			{
				pos.y -= 3.0f * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
			{
				pos.z += 3.0f * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
			{
				pos.z -= 3.0f * Time::DeltaTime();
			}

			tr->SetPosition(pos);*/
	}
	void PlayerScript::Render()
	{
	}
}