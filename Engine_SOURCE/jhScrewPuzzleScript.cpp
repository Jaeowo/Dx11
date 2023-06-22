#include "jhScrewPuzzleScript.h"
#include "jhScrewPuzzle.h"
#include "jhPlayerAttackCol.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"
#include "jhResources.h"

namespace jh
{
	ScrewPuzzleScript::ScrewPuzzleScript()
		:mCount(0)
	{
		std::shared_ptr<AudioClip> screwclip = std::make_shared<AudioClip>();
		screwclip->Load(L"..\\Resources\\Audio\\chain1.wav");
		Resources::Insert<AudioClip>(L"Screw", screwclip);
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

			std::shared_ptr<AudioClip> screwclip = Resources::Find<AudioClip>(L"Screw");
			screwclip->Play();
		}
	}

	void ScrewPuzzleScript::OnCollisionStay(Collider2D* collider)
	{

	}

	void ScrewPuzzleScript::OnCollisionExit(Collider2D* collider)
	{
	}
}