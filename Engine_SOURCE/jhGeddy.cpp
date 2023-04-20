#include "jhGeddy.h"
#include "jhCollider2D.h"

namespace jh
{
	Geddy::Geddy()
	{
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetType(eColliderType::Rect);
		collider->SetSize(Vector2(0.3f, 0.3f));
	}
	Geddy::~Geddy()
	{
	}
	void Geddy::Initalize()
	{
		GameObject::Initalize();
	}
	void Geddy::Update()
	{
		GameObject::Update();
	}
	void Geddy::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Geddy::Render()
	{
		GameObject::Render();
	}
}