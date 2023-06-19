#include "jhScrewPuzzleScript.h"
#include "jhScrewPuzzle.h"
#include "jhPlayerAttackCol.h"

namespace jh
{
	ScrewPuzzleScript::ScrewPuzzleScript()
		:mCount(0)
	{
	}
	ScrewPuzzleScript::~ScrewPuzzleScript()
	{
	}
	void ScrewPuzzleScript::Initalize()
	{
		mScrewPuzzle = dynamic_cast<ScrewPuzzle*>(GetOwner());
	}
	void ScrewPuzzleScript::Update()
	{
	}
	void ScrewPuzzleScript::Render()
	{
	}

	void ScrewPuzzleScript::OnCollisionEnter(Collider2D* collider)
	{
		PlayerAttackCol* attackcol = dynamic_cast<PlayerAttackCol*>(collider->GetOwner());
		if (attackcol != nullptr) 
		{
			mScrewPuzzle->IncrementState();
		}
	}

	void ScrewPuzzleScript::OnCollisionStay(Collider2D* collider)
	{

	}

	void ScrewPuzzleScript::OnCollisionExit(Collider2D* collider)
	{
	}
}