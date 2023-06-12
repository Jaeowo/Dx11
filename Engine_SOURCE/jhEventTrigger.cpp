#include "jhEventTrigger.h"
#include "jhPlayer.h"
#include "jhPlayerManager.h"
#include "jhEventTriggerScript.h"

namespace jh
{
	EventTrigger::EventTrigger()
	{
		AddComponent<EventTriggerScript>();
		Collider2D* Wallcollider = AddComponent<Collider2D>();
		Wallcollider->SetType(eColliderType::Rect);

	}

	EventTrigger::~EventTrigger()
	{
	}

	void EventTrigger::Initalize()
	{
		GameObject::Initalize();

	}
	void EventTrigger::Update()
	{

		GameObject::Update();

	}
	void EventTrigger::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void EventTrigger::Render()
	{
		GameObject::Render();
	}


}