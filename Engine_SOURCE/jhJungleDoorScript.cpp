#include "jhJungleDoorScript.h"
#include "jhInput.h"
#include "jhSceneManager.h"
#include "jhPlayer.h"
#include "jhTime.h"
#include "jhJungleDoor.h"

namespace jh
{
	JungleDoorScript::JungleDoorScript()
		: mElapsedTime(0.0f)
		, mCount(0)
	{
	}
	JungleDoorScript::~JungleDoorScript()
	{
	}
	void JungleDoorScript::Initalize()
	{
		mJungleDoor = dynamic_cast<JungleDoor*>(GetOwner());
	}
	void JungleDoorScript::Update()
	{
		mElapsedTime += Time::DeltaTime();
	}
	void JungleDoorScript::Render()
	{
	}
	void JungleDoorScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void JungleDoorScript::OnCollisionStay(Collider2D* collider)
	{

		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());

		if (playerObj != nullptr)
		{
			if (playerObj->GetPlayerState() == ePlayerState::Idle)
			{
				if (Input::GetKeyDown(eKeyCode::S))
				{
					if (mCount == 0)
					{
						mElapsedTime = 0.0f;
						mCount = 1;
						playerObj->SetCount(0);
						playerObj->SetPlayerState(ePlayerState::EnterDoor);
					}
				}

			}
		}

		

		if (mCount == 1)
		{
			mElapsedTime += Time::DeltaTime();
			if (mElapsedTime >= 3.0f)
			{
				if (mJungleDoor->GetCavetoCave2() == true)
				{
					SceneManager::LoadScene(eSceneType::Cave2);
				}
				else if (mJungleDoor->GetCave2toJungle() == true)
				{
					SceneManager::LoadScene(eSceneType::Jungle);
				}
			}
		}

	}
	void JungleDoorScript::OnCollisionExit(Collider2D* collider)
	{
	}
}