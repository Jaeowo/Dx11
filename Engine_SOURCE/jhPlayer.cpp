#include "jhPlayer.h"
#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhCollider2D.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhTime.h"

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
		, mEventOn(false)
		, mCaveEventOn(false)
		, mHurtTimer(0.0f)
		, mMoveCheck(false)
		, mJungleEventOn(false)

	{
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(Vector3(1.0f, -0.45f, 1.7f));
		mTransform->SetScale(Vector3(0.35f, 0.35f, 1.0f));

		mRotation = (Vector3(0.0f, 0.0f, 0.0f));

		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.1f, 0.22f));
		mCollider->SetCenter(Vector2(-0.015f, -0.01f));

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

		if (mPlayerState != ePlayerState::Hurt && mPlayerState != ePlayerState::FlyHurt)
		{
			mPrevState = mPlayerState;
		}

		if (mIsInvincible)
		{
			mInvincibleTimer += Time::DeltaTime();
			if (mInvincibleTimer >= 1.5f)
			{
				mIsInvincible = false;
			}
		}

		if (mPlayerState == ePlayerState::Hurt || mPlayerState == ePlayerState::FlyHurt)
		{
			mHurtTimer += Time::DeltaTime();
			if (mHurtTimer >= 0.1f)
			{
				mPlayerState = mPrevState;
				mCount = 0;
				mHurtTimer = 0.0f;  
			}
		}
	
		if (mCaveEventOn == true)
		{

		}

		//if (mRotation.y == 180.0f)
		//{
		//	mCollider->SetCenter(Vector2(0.01f, -0.01f));
		//}
		//else
		//{
		//	mCollider->SetCenter(Vector2(-0.015f, -0.01f));
		//}

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