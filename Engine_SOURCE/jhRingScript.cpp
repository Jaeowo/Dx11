#include "jhRingScript.h"
#include "jhPlayer.h"
#include "jhRing.h"

namespace jh
{
	RingScript::RingScript()
		:Script()
	{

	}
	RingScript::~RingScript()
	{
	}
	void RingScript::Initalize()
	{
		mring = dynamic_cast<Ring*>(GetOwner());
	}
	void RingScript::Update()
	{
		
	}
	void RingScript::Render()
	{
	}
	void RingScript::OnCollisionEnter(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());
		mring->SetTouch(true);
		mring->SetCount(false);
	}
	void RingScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void RingScript::OnCollisionExit(Collider2D* collider)
	{
	}
}