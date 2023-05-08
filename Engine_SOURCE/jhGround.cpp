#include "jhGround.h"
#include "jhCollider2D.h"
#include "jhGroundScript.h"

namespace jh
{
	Ground::Ground()
	{
		AddComponent<GroundScript>();
		Collider2D* groundcollider = AddComponent<Collider2D>();
		groundcollider->SetType(eColliderType::Rect);
	}
	Ground::~Ground()
	{
	}
	void Ground::Initalize()
	{
		GameObject::Initalize();
	
	}
	void Ground::Update()
	{
		GameObject::Update();

	}
	void Ground::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Ground::Render()
	{
		GameObject::Render();
	}
}