#include "jhEventTriggerScript.h"
#include "jhPlayer.h"
#include "jhEventTrigger.h"


namespace jh
{
	EventTriggerScript::EventTriggerScript()
		:Script()
	{

	}
	EventTriggerScript::~EventTriggerScript()
	{
	}
	void EventTriggerScript::Initalize()
	{
		meventtrigger = dynamic_cast<EventTrigger*>(GetOwner());
	}
	void EventTriggerScript::Update()
	{

	}
	void EventTriggerScript::Render()
	{
	}
	void EventTriggerScript::OnCollisionEnter(Collider2D* collider)
	{
		Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());
		if (playerObj)
		{
			playerObj->SetCaveEventTrigger(true);
		}


		meventtrigger->Death();
	}
	void EventTriggerScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void EventTriggerScript::OnCollisionExit(Collider2D* collider)
	{
	}
}