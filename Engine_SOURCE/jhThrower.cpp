#include "jhThrower.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhObject.h"
#include "jhAnimator.h"
#include "jhPlayer.h"
#include "jhPlayerManager.h"
#include "jhTime.h"

namespace jh
{
	Thrower::Thrower()
		: mOneCount(false)
		, mTotalTime(0.0f)
		, mRotation (Vector3(0.0f,180.0f,0.0f))
		, mPosition(Vector3(0.0f, 0.0f, 0.0f))
		, mHp (4)
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mTransform->SetScale(Vector3(0.3f, 0.3f, 1.0f));

		SpriteRenderer* gawksr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> gawkmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> gawkmaterial = Resources::Find<Material>(L"GawkMaterial");
		gawksr->SetMaterial(gawkmaterial);
		gawksr->SetMesh(gawkmesh);

		std::shared_ptr<Texture> throwertexture = Resources::Load<Texture>(L"Thrower", L"Thrower\\thrower.png");
		mAnimator->Create(L"ThrowerIdle", throwertexture, Vector2(0.0f, 0.0f), Vector2(100.0f, 70.0f), Vector2::Zero, 6, 0.2f);
		mAnimator->Create(L"ThrowerFollow", throwertexture, Vector2(0.0f, 70.0f), Vector2(100.0f, 70.0f), Vector2::Zero, 6, 0.2f);
		mAnimator->Create(L"ThrowWait", throwertexture, Vector2(0.0f, 140.0f), Vector2(100.0f, 70.0f), Vector2::Zero, 3, 0.2f);
		mAnimator->Create(L"Throw", throwertexture, Vector2(0.0f, 210.0f), Vector2(100.0f, 70.0f), Vector2::Zero, 6, 0.2f);
		mAnimator->Create(L"Hurt", throwertexture, Vector2(0.0f, 280.0f), Vector2(100.0f, 70.0f), Vector2::Zero, 2, 0.2f);

		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.1f, 0.1f));


		mAnimator->Play(L"ThrowerIdle", true);

	
	}
	Thrower::~Thrower()
	{
	}
	void Thrower::Initalize()
	{
		GameObject::Initalize();
		mTargetPosition = PlayerManager::GetPlayer()->GetPlayerPos();
	}
	void Thrower::Update()
	{
		GameObject::Update();
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);
		mTargetPosition = PlayerManager::GetPlayer()->GetPlayerPos();
		mTransform->SetRotation(mRotation);

		switch (mThrowerState)
		{
		case jh::eThrowerState::Idle:
			Idle();
			break;
		case jh::eThrowerState::Follow:
			Follow();
			break;
		case jh::eThrowerState::ThrowWait:
			ThrowWait();
			break;
		case jh::eThrowerState::Throw:
			Throw();
			break;
		case jh::eThrowerState::Hurt:
			Hurt();
			break;
		default:
			break;
		}

	}
	void Thrower::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Thrower::Render()
	{
		GameObject::Render();
	}

	void Thrower::Idle()
	{
	}

	void Thrower::Follow()
	{

		Vector3 Dir = mTargetPosition - mPosition;
		float speed = 0.1f;
		Dir.Normalize();
		mPosition.x += Dir.x * speed * Time::DeltaTime();

		if (mTargetPosition.x < mPosition.x)
		{
			mRotation.y = 180.0f;
		}
		else
		{
			mRotation.y = 0.0f;
		}
	}

	void Thrower::ThrowWait()
	{
	}

	void Thrower::Throw()
	{
	}

	void Thrower::Hurt()
	{
	}

}