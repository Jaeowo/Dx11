#include "jhCameraScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhCamera.h"
#include "jhObject.h"
#include "jhPlayerManager.h"
#include "jhPlayer.h"

namespace jh
{
	CameraScript::CameraScript()
		: Script()
		, mEditorMode(false)
		, mNumber(0)
		, mCaveEvent(false)
	{
	}
	CameraScript::~CameraScript()
	{
	}
	void CameraScript::Initalize()
	{
	}
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Camera* cameraobj = GetOwner()->GetComponent<Camera>();
		cameraobj->SetCaveEvent(mCaveEvent);

		Transform* cameraTransform = GetOwner()->GetComponent<Transform>();
		Vector3 cameraposition;


		if (mEditorMode == true)
		{
			if (mNumber == 0)
			{
				cameraposition.x = 0.0f;
				cameraposition.y = 0.0f;
				cameraposition.z = 0.1f;
				cameraTransform->SetPosition(cameraposition);

				mNumber = 1;
			}
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();

			if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
			{
				pos += 5.0f * tr->Right() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
			{
				pos += 5.0f * -tr->Right() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::NUM_0) == eKeyState::PRESSED)
			{
				pos += 5.0f * tr->Forward() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::NUM_1) == eKeyState::PRESSED)
			{
				pos += 5.0f * -tr->Forward() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
			{
				pos += 5.0f * tr->Up() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
			{
				pos += 5.0f * -tr->Up() * Time::DeltaTime();
			}

			tr->SetPosition(pos);

		}
		else if(cameraobj->GetTarget() != nullptr && mEditorMode == false)
		{
			Transform* targetTransform = cameraobj->GetTarget()->GetComponent<Transform>();
			Vector3 targetposition = targetTransform->GetPosition();

			targetposition.y += 0.1f;
			targetposition.z -= 0.7f;
			cameraposition = targetTransform->Right();
			cameraTransform->SetPosition(targetposition);
		}
			
		if (PlayerManager::GetPlayer() != nullptr)
		{
			if (PlayerManager::GetPlayer()->GetCaveEventTrigger() == true)
			{
				mCaveEvent = true;
			}
			if (mCaveEvent == true)
			{
				cameraposition.x = -1.55f;
				cameraposition.y = -2.25f;
				cameraposition.z = 1.0f;
				cameraTransform->SetPosition(cameraposition);
			}

		}

		if (PlayerManager::GetPlayer() != nullptr)
		{
			if (PlayerManager::GetPlayer()->GetJungleEventTrigger() == true)
			{
				mJungleEvent = true;
			}
			if (mJungleEvent == true)
			{
				cameraposition.x = 0.0f;
				cameraposition.y = 0.0f;
				cameraposition.z = 1.0f;
				cameraTransform->SetPosition(cameraposition);
			}

		}

		
	}
	void CameraScript::Render()
	{
	}
}