#include "jhGawk.h"
#include "jhAnimator.h"
#include "jhTransform.h"
#include "jhResources.h"
#include "jhPlayerManager.h"
#include "jhPlayer.h"
#include "jhTime.h"

namespace jh
{
	Gawk::Gawk()
		: mGawkState(eGawkState::Flying)
		, mHp(4)
		, mCount(0)
		, mTarget(false)
	{
		Animator* mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mTransform->SetPosition(Vector3(0.4f, 1.0f, 1.7f));
		mTransform->SetScale(Vector3(0.29f, 0.29f, 1.0f));
	
		std::shared_ptr<Texture> gawktexture = Resources::Load<Texture>(L"Gawk", L"Gawk\\sprGawkSheet_81x70.png");
		mAnimator->Create(L"GawkFlying", gawktexture, Vector2(0.0f, 0.0f), Vector2(81.0f, 70.0f), Vector2::Zero, 6, 0.2f);
		mAnimator->Create(L"GawkUpsideDown", gawktexture, Vector2(0.0f, 70.0f), Vector2(81.0f, 70.0f), Vector2::Zero, 2, 0.4f);
		mAnimator->Create(L"GawkUpsideDowntoFly", gawktexture, Vector2(0.0f, 140.0f), Vector2(81.0f, 70.0f), Vector2::Zero, 11, 0.2f);
		mAnimator->Create(L"GawkHurt", gawktexture, Vector2(0.0f, 210.0f), Vector2(81.0f, 70.0f), Vector2::Zero, 1, 0.2f);

		mAnimator->Play(L"GawkFlying", true);
	
	}
	Gawk::~Gawk()
	{
	}
	void Gawk::Initalize()
	{
		GameObject::Initalize();

	}
	void Gawk::Update()
	{
		GameObject::Update();
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mTargetPosition = PlayerManager::GetPlayer()->GetPlayerPos();
		
		mMonsterPosition = mTransform->GetPosition();

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

		Vector3 Dir = mTargetPosition - mMonsterPosition;
		Dir.Normalize();

		mMonsterPosition += (mTargetPosition * Dir) * (Time::DeltaTime() /10.0f) ;

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
			mCount = 1;
		}
	}
	void Gawk::Hurt()
	{
		if (mCount == 0)
		{
			mAnimator->Play(L"GawkHurt", false);
			mCount = 1;
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