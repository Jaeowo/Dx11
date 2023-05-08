#include "jhChangeMonsterState.h"
#include "jhChangeGawk.h"

namespace jh
{
	ChangeMonsterState::ChangeMonsterState()
	{
		AddComponent<ChangeGawk>();
		Collider2D* doorcollider = AddComponent<Collider2D>();
		doorcollider->SetType(eColliderType::Rect);
	}
	ChangeMonsterState::~ChangeMonsterState()
	{
	}
	void ChangeMonsterState::Initalize()
	{
		GameObject::Initalize();

	}
	void ChangeMonsterState::Update()
	{
		GameObject::Update();

	}
	void ChangeMonsterState::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void ChangeMonsterState::Render()
	{
		GameObject::Render();
	}
}