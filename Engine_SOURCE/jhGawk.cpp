#include "jhGawk.h"
#include "jhAnimator.h"
#include "jhTransform.h"
#include "jhResources.h"
#include "jhPlayerManager.h"
#include "jhPlayer.h"
#include "jhTime.h"
#include "jhGawkScript.h"
#include "jhCollider2D.h"
#include "jhSpriteRenderer.h"

namespace jh
{
	Gawk::Gawk()
		: mGawkState(eGawkState::UpsideDown)
		, mHp(4)
		, mCount(0)
		, mTarget(false)
		, mElapsedTime(0.0f)
	{
		Animator* mAnimator = AddComponent<Animator>();

		SpriteRenderer* gawksr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> gawkmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> gawkmaterial = Resources::Find<Material>(L"GawkMaterial");
		gawksr->SetMaterial(gawkmaterial);
		gawksr->SetMesh(gawkmesh);

		std::shared_ptr<Texture> gawktexture = Resources::Load<Texture>(L"Gawk", L"Gawk\\sprGawkSheet_81x70.png");
		mAnimator->Create(L"GawkFlying", gawktexture, Vector2(0.0f, 0.0f), Vector2(81.0f, 70.0f), Vector2::Zero, 6, 0.2f);
		mAnimator->Create(L"GawkUpsideDown", gawktexture, Vector2(0.0f, 70.0f), Vector2(81.0f, 70.0f), Vector2::Zero, 2, 0.4f);
		mAnimator->Create(L"GawkUpsideDowntoFly", gawktexture, Vector2(0.0f, 140.0f), Vector2(81.0f, 70.0f), Vector2::Zero, 11, 0.15f);
		mAnimator->Create(L"GawkHurt", gawktexture, Vector2(0.0f, 210.0f), Vector2(81.0f, 70.0f), Vector2::Zero, 1, 0.2f);

		mAnimator->Play(L"GawkFlying", true);
	
		mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(4.5f, 4.5f));
		//mCollider->SetCenter(Vector2(0.5f,0.0f))

	}
	Gawk::~Gawk()
	{
	}
	void Gawk::Initalize()
	{
		AddComponent<GawkScript>();
		GameObject::Initalize();

	}
	void Gawk::Update()
	{
		GameObject::Update();
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mTargetPosition = PlayerManager::GetPlayer()->GetPlayerPos();
		
		mMonsterPosition = mTransform->GetPosition();

		mElapsedTime += Time::DeltaTime();

		if (mHp <= 0)
		{
			Death();
		}

		switch (mGawkState)
		{
		case jh::eGawkState::Flying:
			Flying();
			break;
		case jh::eGawkState::UpsideDown:
			UpsideDown();
			break;
		case jh::eGawkState::UpsideDowntoFly:
			UpsideDowntoFly();
			break;
		case jh::eGawkState::Hurt:
			Hurt();
			break;
		case jh::eGawkState::Sturn:
			Sturn();
			break;
		default:
			break;
		}

	}
	void Gawk::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Gawk::Render()
	{
		GameObject::Render();
	}
	void Gawk::Flying()
	{
		if (mCount == 0)
		{
			mAnimator->Play(L"GawkFlying", true);
			mCount = 1;
		}

		float speed = 0.18f; // 기본 이동 속도
		float bounceHeight = 0.00005f; // 튀는 높이
		float bounceSpeed = 5.0f; // 튀는 속도

		float yDistance = abs(mTargetPosition.y - mMonsterPosition.y);
		float speedFactor = 1.0f + yDistance * 0.3f;

		Vector3 Dir = mTargetPosition - mMonsterPosition;
		Dir.Normalize();

		mMonsterPosition += Dir * speed * speedFactor * Time::DeltaTime(); 

		mElapsedTime += Time::DeltaTime();
		float bounceY = (bounceHeight * speedFactor) * sin(bounceSpeed * mElapsedTime); 

		mMonsterPosition.y = mMonsterPosition.y - bounceY;

		mTransform->SetPosition(mMonsterPosition);


	}
	void Gawk::UpsideDown()
	{
		if (mCount == 0)
		{
			mAnimator->Play(L"GawkUpsideDown", true);
			mCount = 1;

			if (mTarget == true)
			{
				mCount = 0;
				mGawkState = eGawkState::UpsideDowntoFly;
			}
		}
	}
	void Gawk::UpsideDowntoFly()
	{
		if (mCount == 0)
		{
			mAnimator->Play(L"GawkUpsideDowntoFly", false);
			mElapsedTime = 0.0f;
			mCount = 1;
			mCollider->SetSize(Vector2(0.2f, 0.2f));
	
		}
		if (mElapsedTime >= 0.8f)
		{
			mCount = 0;
			mGawkState = eGawkState::Flying;
		}
	}
	void Gawk::Hurt()
	{
		if (mCount == 0)
		{
			mAnimator->Play(L"GawkHurt", false);
			mHp -= 1;
			mElapsedTime = 0.0f;
			mCount = 1;
		}
		if (mElapsedTime >= 0.5f)
		{
			mCount = 0;
			mGawkState = eGawkState::Flying;
		}
	}
	void Gawk::Sturn()
	{
		if (mCount == 0)
		{
			mAnimator->Play(L"GawkHurt", false);
			mCount = 1;
		}
	}

}