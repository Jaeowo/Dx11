#include "jhSlope.h"
#include "jhSlopeScript.h"

namespace jh
{
	Slope::Slope()
	{
		AddComponent<SlopeScript>();
		Collider2D* groundcollider = AddComponent<Collider2D>();
		groundcollider->SetType(eColliderType::Rect);
	}
	Slope::~Slope()
	{
	}
	void Slope::Initalize()
	{
		GameObject::Initalize();

	}
	void Slope::Update()
	{
		GameObject::Update();

	}
	void Slope::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Slope::Render()
	{
		GameObject::Render();
	}
}