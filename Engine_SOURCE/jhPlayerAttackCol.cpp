#include "jhPlayerAttackCol.h"
#include "jhCollider2D.h"
#include "jhPlayerManager.h"
#include "jhPlayer.h"

namespace jh
{
	PlayerAttackCol::PlayerAttackCol()
	{
		mTransform = GetComponent<Transform>();
		mPlayerPos = PlayerManager::GetPlayer()->GetPlayerPos();
		mTransform->SetPosition(mPlayerPos);
		mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.07f, 0.07f));

		if (PlayerManager::GetPlayer()->GetPlayerRotation().y == 180.0f)
		{
			mCollider->SetCenter(Vector2(-0.025f, -0.01f));
		}
		else
		{
			mCollider->SetCenter(Vector2(0.025f, -0.01f));
		}
		
	}

	PlayerAttackCol::~PlayerAttackCol()
	{
	}

	void PlayerAttackCol::Initalize()
	{
		GameObject::Initalize();

	}
	void PlayerAttackCol::Update()
	{

		GameObject::Update();

	}
	void PlayerAttackCol::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void PlayerAttackCol::Render()
	{
		GameObject::Render();
	}


}