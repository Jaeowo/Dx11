#include "jhDoorScript.h"
#include "jhInput.h"
#include "jhSceneManager.h"
#include "jhPlayer.h"
#include "jhTime.h"

namespace jh
{
	DoorScript::DoorScript()
		: mElapsedTime(0.0f)
		, mCount(0)
	{
	}
	DoorScript::~DoorScript()
	{
	}
	void DoorScript::Initalize()
	{
	}
	void DoorScript::Update()
	{
		mElapsedTime += Time::DeltaTime();
	}
	void DoorScript::Render()
	{
	}
	void DoorScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void DoorScript::OnCollisionStay(Collider2D* collider)
	{

		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());

		

		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mCount == 0)
			{
				mElapsedTime = 0.0f;
				mCount = 1;
			}			
			playerObj->SetCount(0);
			playerObj->SetPlayerState(ePlayerState::EnterDoor);
		
		}
		if (mCount == 1)
		{
			mElapsedTime += Time::DeltaTime();
			if (mElapsedTime >= 3.0f)
			{
				SceneManager::LoadScene(eSceneType::Cave);
			}
		}

	}
	void DoorScript::OnCollisionExit(Collider2D* collider)
	{
	}
}