#include "jhChestScript.h"
#include "jhChest.h"
#include "jhPlayer.h"
#include "jhInput.h"
#include "jhPlayerManager.h"
#include "jhTransform.h"

namespace jh
{
	ChestScript::ChestScript()
		:Script()
	{

	}
	ChestScript::~ChestScript()
	{
	}
	void ChestScript::Initalize()
	{
		mchest = dynamic_cast<Chest*>(GetOwner());
	}
	void ChestScript::Update()
	{

	}
	void ChestScript::Render()
	{
	}
	void ChestScript::OnCollisionEnter(Collider2D* collider)
	{
	
	}
	void ChestScript::OnCollisionStay(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());

		if (Input::GetKeyDown(eKeyCode::R))
		{
			//playerObj->SetCount(0);
			//playerObj->SetPlayerState(ePlayerState::FlyGrab);
			//mchest->SetCount(false);
			mchest->SetState(eChestState::Open);
		}
	}
	void ChestScript::OnCollisionExit(Collider2D* collider)
	{
	}
}