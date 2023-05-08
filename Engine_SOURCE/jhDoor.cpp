#include "jhDoor.h"
#include "jhDoorScript.h"

namespace jh
{
	Door::Door()
	{
		AddComponent<DoorScript>();
		Collider2D* doorcollider = AddComponent<Collider2D>();
		doorcollider->SetType(eColliderType::Rect);
	}
	Door::~Door()
	{
	}
	void Door::Initalize()
	{
		GameObject::Initalize();

	}
	void Door::Update()
	{
		GameObject::Update();

	}
	void Door::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Door::Render()
	{
		GameObject::Render();
	}
}