#include "jhChangeGawk.h"
#include "jhGawk.h"

namespace jh
{
	ChangeGawk::ChangeGawk()
		:mCount(0)
	{
	}
	ChangeGawk::~ChangeGawk()
	{
	}
	void ChangeGawk::Initalize()
	{
	}
	void ChangeGawk::Update()
	{
	}
	void ChangeGawk::Render()
	{
	}
	void ChangeGawk::OnCollisionEnter(Collider2D* collider)
	{
		if (mCount == 0)
		{
			Gawk* gawkObj = dynamic_cast<Gawk*>(collider->GetOwner());

			gawkObj->SetPlayerState(eGawkState::UpsideDowntoFly);

			mCount = 1;
		}
	
	}
	void ChangeGawk::OnCollisionStay(Collider2D* collider)
	{
	}
	void ChangeGawk::OnCollisionExit(Collider2D* collider)
	{
	}
}
