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
		, mHp(5)
		, mBeeState(eBeeState::Idle)
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

		mTotalTime += Time::DeltaTime();

		if (mHp <= 0)
		{
			mBeeState = eBeeState::Death;
			mOneCount = false;
		}

		switch (mBeeState)
		{
		case jh::eBeeState::Idle:
			Idle();
			break;
		case jh::eBeeState::Attack:
			Attack();
			break;
		case jh::eBeeState::Follow:
			Follow();
			break;
		case jh::eBeeState::HitWall:
			HitWall();
			break;
		case jh::eBeeState::Hit:
			Hit();
			break;
		case jh::eBeeState::Death:
			BeeDeath();
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
		if (mOneCount == false)
		{
			mAnimator->Play(L"BeeIdle", true);
			mOneCount = true;
		}
	}

	void Bee::Attack()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"BeeAttack", false);
			mOneCount = true;
		}
	}

	void Bee::Follow()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"BeeIdle", true);
			mOneCount = true;
		}
	}

	void Bee::HitWall()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"HitWall", false);
			mOneCount = true;
		}
	}

	void Bee::Hit()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"BeeHit", false);
			mOneCount = true;
		}
	}

	void Bee::BeeDeath()
	{
		if (mOneCount == false)
		{
			mTotalTime = 0.0f;
			mOneCount = true;
		}

		if (mTotalTime >= 0.5f)
		{
			Death();
		}
	}

}