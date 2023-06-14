#include "jhBeeHive.h"

namespace jh
{
	BeeHive::BeeHive()
		: mPosition(Vector3(0.0f, 0.0f, 0.0f))
		, mOneCount(false)
		, mTotalTime(0.0f)
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.1f, 0.1f));

	}
	BeeHive::~BeeHive()
	{
	}
	void BeeHive::Initalize()
	{
		GameObject::Initalize();
	}
	void BeeHive::Update()
	{
		GameObject::Update();

		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);




	}
	void BeeHive::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void BeeHive::Render()
	{
		GameObject::Render();
	}

}