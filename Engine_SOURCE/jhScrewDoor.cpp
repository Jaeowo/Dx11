#include "jhScrewDoor.h"
#include "jhStoneDoor.h"
#include "jhObject.h"
#include "jhScrewPiece.h"
#include "jhScrewPuzzle.h"

namespace jh
{
	ScrewDoor::ScrewDoor()
		: mOneCount(false)
	{
		
		mStoneDoor = object::Instantiate<StoneDoor>(eLayerType::BackGround);
		mStoneDoor->SetPosition(Vector3(1.05f, -0.88f, 1.7f));
		mStoneDoor->SetScale(Vector3(0.45f, 0.47f, 1.0f));
		mStoneDoor->SetRotation(Vector3(0.0f, 0.0f, 180.0f));
		mStoneDoor->SetCenter(Vector2(-0.05f, 0.0f));

		ScrewPiece* screwpieceobj = object::Instantiate<ScrewPiece>(eLayerType::BackGround);
		screwpieceobj->SetPosition(Vector3(0.53f, -0.82f, 1.7f));

		mScrewPuzzle1 = object::Instantiate<ScrewPuzzle>(eLayerType::BackGround);
		mScrewPuzzle1->SetPosition(Vector3(0.53f, -0.75f, 1.7f));

		mScrewPuzzle2 = object::Instantiate<ScrewPuzzle>(eLayerType::BackGround);
		mScrewPuzzle2->SetPosition(Vector3(0.53f, -0.82f, 1.7f));
		mScrewPuzzle2->SetPuzzleState(ePuzzleState::N9);

		mScrewPuzzle3 = object::Instantiate<ScrewPuzzle>(eLayerType::BackGround);
		mScrewPuzzle3->SetPosition(Vector3(0.53f, -0.885f, 1.7f));
		mScrewPuzzle3->SetPuzzleState(ePuzzleState::N13);
	}
	ScrewDoor::~ScrewDoor()
	{
	}
	void ScrewDoor::Initalize()
	{
		GameObject::Initalize();
	}
	void ScrewDoor::Update()
	{
		GameObject::Update();

		if (mScrewPuzzle1->GetClear() == true &&
			mScrewPuzzle2->GetClear() == true &&
			mScrewPuzzle3->GetClear() == true)
		{
			if (mOneCount == false)
			{
				mStoneDoor->SetOpenTrigger(true);
				mStoneDoor->SetCount(false);
				mOneCount = true;
			}
		}
	}
	void ScrewDoor::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void ScrewDoor::Render()
	{
		GameObject::Render();
	}

}