#include "jhBee.h"

namespace jh
{
	Bee::Bee()
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
	Bee::~Bee()
	{
	}
	void Bee::Initalize()
	{
		GameObject::Initalize();
	}
	void Bee::Update()
	{
		GameObject::Update();

		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);




	}
	void Bee::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Bee::Render()
	{
		GameObject::Render();
	}

}