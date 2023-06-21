#include "jhBee.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhObject.h"
#include "jhAnimator.h"
#include "jhPlayer.h"
#include "jhPlayerManager.h"
#include "jhTime.h"
#include "jhBeeScript.h"
#include "jhPlayerManager.h"
#include "jhBeeHive.h"

namespace jh
{
	Bee::Bee()
		: mOneCount(false)
		, mTotalTime(0.0f)
		, mRotation(Vector3(0.0f, 0.0f, 0.0f))
		, mPosition(Vector3(0.0f, 0.0f, 0.0f))
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
		mTargetPosition = PlayerManager::GetPlayer()->GetPlayerPos();
		AddComponent<BeeScript>();
		PlayerManager::GetBeeHive()->IncreasePhaseBee();
	}
	void Bee::Update()
	{
		GameObject::Update();
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);
		mTargetPosition = PlayerManager::GetPlayer()->GetPlayerPos();
		mTransform->SetRotation(mRotation);

		mTotalTime += Time::DeltaTime();

		if (mHp <= 0)
		{
			mBeeState = eBeeState::Die;
			mOneCount = false;
		}

		switch (mBeeState)
		{
		case jh::eBeeState::LeftSpawn:
			LeftSpawn();
			break;
		case jh::eBeeState::RightSpawn:
			RightSpawn();
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
		case jh::eBeeState::Die:
			Die();
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

	void Bee::LeftSpawn()
	{
		if (mOneCount == false)
		{
			mPosition = (Vector3(-0.09f, 0.12f, 1.7f));
			mAnimator->Play(L"BeeIdle", true);
			mOneCount = true;
		}

		mPosition.y += sin(Time::DeltaTime()) * 0.01f;

		mPosition.x -= 0.00001f;
	}

	void Bee::RightSpawn()
	{
		if (mOneCount == false)
		{
			mPosition = (Vector3(0.09f, 0.12f, 1.7f));
			mAnimator->Play(L"BeeIdle", true);
			mOneCount = true;
		}
	}

	void Bee::Attack()
	{
	}

	void Bee::Follow()
	{
	}

	void Bee::HitWall()
	{
	}

	void Bee::Hit()
	{
	}

	void Bee::Die()
	{
		if (mOneCount == false)
		{
			mTotalTime = 0.0f;
			mOneCount = true;
		}

		if (mTotalTime >= 0.5f)
		{
			PlayerManager::GetBeeHive()->IncreaseDeadBee();
			Death();
		}
		
	}

}