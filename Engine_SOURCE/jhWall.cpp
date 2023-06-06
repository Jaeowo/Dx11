#include "jhWall.h"
#include "jhWallScript.h"
#include "jhCollider2D.h"

namespace jh
{
	Wall::Wall()
	{
		AddComponent<WallScript>();
		Collider2D* Wallcollider = AddComponent<Collider2D>();
		Wallcollider->SetType(eColliderType::Rect);
	}
	Wall::~Wall()
	{
	}
	void Wall::Initalize()
	{
		GameObject::Initalize();

	}
	void Wall::Update()
	{
		GameObject::Update();

	}
	void Wall::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Wall::Render()
	{
		GameObject::Render();
	}
}