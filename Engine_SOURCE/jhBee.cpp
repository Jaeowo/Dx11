#include "jhBee.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhObject.h"
#include "jhAnimator.h"
#include "jhPlayer.h"
#include "jhPlayerManager.h"
#include "jhTime.h"
#include "jhBeeScript.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"
#include "jhSmallDustEffect.h"


namespace jh
{
	Bee::Bee()
		: mOneCount(false)
		, mTotalTime(0.0f)
		, mRotation(Vector3(0.0f, 0.0f, 0.0f))
		, mPosition(Vector3(0.0f, 0.0f, 0.0f))
		, mHp(5)
		, mBeeState(eBeeState::Idle)
		, mIsDirectionSet(false)
		, mSpeed(0.8f)

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

		std::shared_ptr<AudioClip> beefollow = std::make_shared<AudioClip>();
		beefollow->Load(L"..\\Resources\\Audio\\Bee\\BeeCharge.wav");
		Resources::Insert<AudioClip>(L"BeeFollow", beefollow);

		std::shared_ptr<AudioClip> beeattack = std::make_shared<AudioClip>();
		beeattack->Load(L"..\\Resources\\Audio\\Bee\\beetleChirp.wav");
		Resources::Insert<AudioClip>(L"BeeAttack", beeattack);

		std::shared_ptr<AudioClip> beespawn = std::make_shared<AudioClip>();
		beespawn->Load(L"..\\Resources\\Audio\\Bee\\BeeSpawn.wav");
		Resources::Insert<AudioClip>(L"BeeSpawn", beespawn);
	}
	Bee::~Bee()
	{
	}
	void Bee::Initalize()
	{
		GameObject::Initalize();
		mTargetPosition = PlayerManager::GetPlayer()->GetPlayerPos();
		AddComponent<BeeScript>();

		std::shared_ptr<AudioClip> beespawn = Resources::Find<AudioClip>(L"BeeSpawn");
		beespawn->Play();


		

	}
	void Bee::Update()
	{
		GameObject::Update();
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mPreviousePos = mPosition;
		mTransform->SetPosition(mPosition);
		mTargetPosition = PlayerManager::GetPlayer()->GetPlayerPos();
		mTransform->SetRotation(mRotation);

		mTotalTime += Time::DeltaTime();


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
			mTotalTime = 0.0f;
			mAnimator->Play(L"BeeIdle", true);
			mOneCount = true;
		}

		float speed = 0.000015f; // 왼쪽으로 이동하는 속도
		float bounceHeight = 0.000025f; // 튀는 높이
		float bounceSpeed = 2.5f; // 튀는 속도

		float bounceY = bounceHeight * sin(bounceSpeed * mTotalTime);

		mPosition.y += bounceY;
		mPosition.x -= speed;

		if (mTotalTime >= 2.0f)
		{
			mBeeState = eBeeState::Follow;
			mOneCount = false;
		}
	}

	void Bee::RightSpawn()
	{
		if (mOneCount == false)
		{
			mPosition = (Vector3(0.09f, 0.12f, 1.7f));
			mRotation.y = 180.0f;
			mAnimator->Play(L"BeeIdle", true);
			mOneCount = true;
		}

		float speed = 0.000009f; // 왼쪽으로 이동하는 속도
		float bounceHeight = 0.00002f; // 튀는 높이
		float bounceSpeed = 2.0f; // 튀는 속도

		float bounceY = bounceHeight * sin(bounceSpeed * mTotalTime);

		mPosition.y += bounceY;
		mPosition.x += speed;
	}

	void Bee::Attack()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"BeeAttack", false);

			std::shared_ptr<AudioClip> beefollow = Resources::Find<AudioClip>(L"BeeFollow");
			beefollow->Play();
			mTotalTime = 0.0f;
			mOneCount = true;
		}

		if (mTotalTime >= 0.2f)
		{
			if (!mIsDirectionSet)
			{

				mTargetPosition.y -= 0.06f;

				Vector2 playerPos2D(mTargetPosition.x, mTargetPosition.y);
				Vector2 Bee2D(mPosition.x, mPosition.y);

				mDirection = playerPos2D - Bee2D;
				mDirection.Normalize();

				float angle = std::atan2(mDirection.y, mDirection.x) * 180.0f / XM_PI;

				mTransform->SetRotation(Vector3(0.0f, 0.0f, angle));

				mIsDirectionSet = true;
			}

			if (mIsDirectionSet)
			{
				Vector2 velocity = mDirection * mSpeed;
				SetPosition(mTransform->GetPosition() + Vector3(velocity.x, velocity.y, 0.0f) * Time::DeltaTime());
			}
		}


		if (mTotalTime >= 5.0f)
		{
			mBeeState = eBeeState::Follow;
			mOneCount = false;
		}
	}

	void Bee::Follow()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"BeeIdle", true);
			
			mTotalTime = 0.0f;
			mOneCount = true;
		}
		float speed = 0.2f;

		float yDistance = abs(mTargetPosition.y - mPosition.y);

		Vector3 Dir = mTargetPosition - mPosition;
		Dir.Normalize();
		mPosition += Dir * speed * Time::DeltaTime();

		if (mTargetPosition.x < mPosition.x)
		{
			mRotation.y = 0.0f;
		}
		else
		{
			mRotation.y = 180.0f;
		}

		if (mTotalTime >= 1.5f)
		{
			mBeeState = eBeeState::Attack;
			mOneCount = false;
		}
		
	}

	void Bee::HitWall()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"HitWall", false);
			mTotalTime = 0.0f;
			mIsDirectionSet = false;
			mOneCount = true;
		}

		if (mTotalTime >= 1.0f)
		{
			mBeeState = eBeeState::Follow;
			mOneCount = false;
		}

	}

	void Bee::Hit()
	{
		if (mOneCount == false)
		{
			mHp -= 1;
			mAnimator->Play(L"BeeHit", false);
			mTotalTime = 0.0f;
			mOneCount = true;
		}

		if (mTotalTime >= 0.4f)
		{
			if (mHp > 0)
			{
				mBeeState = eBeeState::Follow;
				mOneCount = false;
			}
			else
			{
				mBeeState = eBeeState::Die;
				mOneCount = false;
			}
		}
	}

	void Bee::Die()
	{
		if (mOneCount == false)
		{

			SmallDustEffect* smalldusteffect = object::Instantiate<SmallDustEffect>(eLayerType::Effect);
			smalldusteffect->SetPosition(mPosition);

			mOneCount = true;
			mTotalTime = 0.0f;
		}

		if (mTotalTime >= 0.3f)
		{
			Death();
		}
		
	}

}