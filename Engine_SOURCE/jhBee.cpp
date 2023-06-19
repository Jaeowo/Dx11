#include "jhBee.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhObject.h"
#include "jhAnimator.h"
#include "jhPlayer.h"
#include "jhPlayerManager.h"
#include "jhTime.h"

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

		mTransform->SetScale(Vector3(0.3f, 0.3f, 1.0f));

		SpriteRenderer* gawksr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> gawkmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> gawkmaterial = Resources::Find<Material>(L"GawkMaterial");
		gawksr->SetMaterial(gawkmaterial);
		gawksr->SetMesh(gawkmesh);

		std::shared_ptr<Texture> beetexture = Resources::Load<Texture>(L"Bee", L"Bee\\sprBee_62x59.png");
		mAnimator->Create(L"BeeIdle", beetexture, Vector2(0.0f, 0.0f), Vector2(62.0f, 59.0f), Vector2::Zero, 8, 0.2f);
		mAnimator->Create(L"BeeAttack", beetexture, Vector2(0.0f, 59.0f), Vector2(62.0f, 59.0f), Vector2::Zero, 5, 0.2f);
		mAnimator->Create(L"HitWall", beetexture, Vector2(0.0f, 118.0f), Vector2(62.0f, 59.0f), Vector2::Zero, 4, 0.2f);
		mAnimator->Create(L"BeeHit", beetexture, Vector2(0.0f, 177.0f), Vector2(62.0f, 59.0f), Vector2::Zero, 1, 0.2f);

		mAnimator->Play(L"BeeIdle", true);

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

		switch (mBeeState)
		{
		case jh::eBeeState::Idle:
			Idle();
			break;
		case jh::eBeeState::Attack:
			Attack();
			break;
		case jh::eBeeState::HitWall:
			HitWall();
			break;
		case jh::eBeeState::Hit:
			Hit();
			break;
		case jh::eBeeState::Death:
			Death();
			break;
		default:
			break;
		}
	}
	void Bee::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Bee::Render()
	{
		GameObject::Render();
	}

	void Bee::Idle()
	{
	}

	void Bee::Attack()
	{
	}

	void Bee::HitWall()
	{
	}

	void Bee::Hit()
	{
	}

	void Bee::Death()
	{
	}

}