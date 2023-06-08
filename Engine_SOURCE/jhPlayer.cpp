#include "jhPlayer.h"
#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhCollider2D.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"

namespace jh
{
	Player::Player()
		: mbGround(false)
		, mCount(0)               
		, mIsFlyingDown(false)
		, mIsFly(false)
		, mIsJumping(false)
		, mvelocityzero(false)
		, mHp(5)
		, mCoin(0)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(Vector3(1.0f, -0.48f, 1.7f));
		mTransform->SetScale(Vector3(0.35f, 0.35f, 1.0f));

		mRotation = (Vector3(0.0f, 0.0f, 0.0f));

		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.1f, 0.28f));
		//mCollider->SetCenter(Vector2(-0.015f, -0.02f));

		//Vector3 ColliderPos = mCollider->GetPosition();
		//Vector2 Center = (Vector2(-0.55f, -0.02f));
		//Vector3 NewColliderPos = ColliderPos + Vector3(Center.x, Center.y, 0.0f);
		//mCollider->SetPosition(NewColliderPos);

		SpriteRenderer* standsr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> standmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> standmaterial = Resources::Find<Material>(L"Standmaterial");
		standsr->SetMaterial(standmaterial);
		standsr->SetMesh(standmesh);
		
	}
	Player::~Player()
	{
	}
	void Player::Initalize()
	{
		GameObject::Initalize();
		AddComponent<PlayerScript>();
	}
	void Player::Update()
	{
		if (mCollider)
		{
			mTransform->SetRotation(mRotation);
		}
		mCollider = GetComponent<Collider2D>();
		mTransform->SetRotation(mRotation);
		

		GameObject::Update();

	}
	void Player::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Player::Render()
	{
		GameObject::Render();
	}
}