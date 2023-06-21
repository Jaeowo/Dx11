#include "jhBeeHive.h"
#include "jhBeeHive.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhObject.h"
#include "jhAnimator.h"
#include "jhPlayer.h"
#include "jhPlayerManager.h"
#include "jhTime.h"
#include "jhBee.h"

namespace jh
{
	BeeHive::BeeHive()
		: mPosition(Vector3(0.0f, 0.0f, 0.0f))
		, mOneCount(false)
		, mTotalTime(0.0f)
		, mSpawnTimer(0.0f)
		, mPhaseTimer(0.0f)
		, mDeadBees(0)
		, mBeeHiveState(eBeeHiveState::Idle)
		, mPhaseMove (false)
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.1f, 0.1f));

		mTransform->SetScale(Vector3(0.6f, 0.6f, 1.0f));

		SpriteRenderer* gawksr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> gawkmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> gawkmaterial = Resources::Find<Material>(L"GawkMaterial");
		gawksr->SetMaterial(gawkmaterial);
		gawksr->SetMesh(gawkmesh);


		std::shared_ptr<Texture> beehivetexture = Resources::Load<Texture>(L"BeeHive", L"Bee\\Beehive\\buzzing_strip7.png");
		std::shared_ptr<Texture> beehivetexture2 = Resources::Load<Texture>(L"BeeHive", L"Bee\\Beehive\\broken.png");
		std::shared_ptr<Texture> beehivetexture3 = Resources::Load<Texture>(L"BeeHive", L"Bee\\Beehive\\spr_Beehive_139x95.png");
	
		mAnimator->Create(L"Buzzing", beehivetexture, Vector2(0.0f, 0.0f), Vector2(139.0f, 95.0f), Vector2::Zero, 7, 0.2f);
		mAnimator->Create(L"Broken", beehivetexture2, Vector2(0.0f, 0.0f), Vector2(139.0f, 95.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"Idle", beehivetexture3, Vector2(0.0f, 0.0f), Vector2(139.0f, 95.0f), Vector2::Zero, 1, 0.2f);

		mAnimator->Play(L"Idle", false);
		
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

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);

		mSpawnTimer += Time::DeltaTime();
		mPhaseTimer += Time::DeltaTime();

		switch (mBeeHiveState)
		{
		case jh::eBeeHiveState::Idle:
			Idle();
			break;
		case eBeeHiveState::Phase1:
			Phase1();
			break;
		case eBeeHiveState::Phase2:
			Phase2();
			break;
		case eBeeHiveState::Phase3:
			Phase3();
			break;
		case eBeeHiveState::Phase4:
			Phase4();
			break;
		case eBeeHiveState::Phase5:
			Phase5();
			break;
		case jh::eBeeHiveState::Broken:
			Broken();
			break;
		default:
			break;
		}
	}
	void BeeHive::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void BeeHive::Render()
	{
		GameObject::Render();
	}

	void BeeHive::Idle()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Idle", false);
			mOneCount = true;
		}

		if (mPhaseTimer >= 3.0f)
		{
			mBeeHiveState = eBeeHiveState::Phase1;
			mOneCount = false;
		}
	}


	void BeeHive::Phase1()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Buzzing", true);
			mOneCount = true;
		}

		if (mPhaseBeeCount < 2 && mSpawnTimer >= 2.0f)
		{
			mSpawnTimer = 0.0f;
			SpawnBees(eBeeState::LeftSpawn);
		}

		if (GetPhaseBee() == 0)
		{
			mPhaseTimer = 0.0f;
			mPhaseMove = true;
		}

		if (mPhaseMove == true && mPhaseTimer >= 4.0f)
		{
			mPhaseMove = false;
			mOneCount = false;
			mBeeHiveState = eBeeHiveState::Phase2;
			mPhaseTimer = 0.0f;
		}
	}


	void BeeHive::Phase2()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Buzzing", true);
			mOneCount = true;
		}

		if (mPhaseBeeCount < 2 && mSpawnTimer >= 2.0f)
		{
			mSpawnTimer = 0.0f;
			SpawnBees(eBeeState::RightSpawn);
		}

		if (mPhaseBeeCount == 0)
		{
			mPhaseTimer = 0.0f;
			mPhaseMove = true;
		}

		if (mPhaseMove == true && mPhaseTimer >= 4.0f)
		{
			mPhaseMove = false;
			mOneCount = false;
			mBeeHiveState = eBeeHiveState::Phase2;
			mPhaseTimer = 0.0f;
		}
	}

	void BeeHive::Phase3()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Buzzing", true);
			mOneCount = true;
		}

		if (mPhaseBeeCount < 4 && mSpawnTimer >= 2.0f)
		{
			mSpawnTimer = 0.0f;
			SpawnBees(eBeeState::LeftSpawn);
		}

		if (mPhaseBeeCount == 0)
		{
			mPhaseTimer = 0.0f;
			mPhaseMove = true;

		}

		if (mPhaseBeeCount == 0 && mPhaseTimer >= 4.0f)
		{
			mPhaseMove = false;
			mOneCount = false;
			mBeeHiveState = eBeeHiveState::Phase4;
			mPhaseTimer = 0.0f;
		}
	}

	void BeeHive::Phase4()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Buzzing", true);
			mOneCount = true;
		}

		if (mPhaseBeeCount < 4 && mSpawnTimer >= 2.0f)
		{
			mSpawnTimer = 0.0f;
			SpawnBees(eBeeState::RightSpawn);
		}

		if (mPhaseBeeCount == 0)
		{
			mPhaseTimer = 0.0f;
			mPhaseMove = true;

		}

		if (mPhaseBeeCount == 0 && mPhaseTimer >= 4.0f)
		{
			mPhaseMove = false;
			mOneCount = false;
			mBeeHiveState = eBeeHiveState::Phase5;
			mPhaseTimer = 0.0f;
		}
	}

	void BeeHive::Phase5()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Buzzing", true);
			mOneCount = true;
		}

		if (mPhaseBeeCount < 6 && mSpawnTimer >= 2.0f)
		{
			mSpawnTimer = 0.0f;
			SpawnBees(eBeeState::LeftSpawn);
		}

		if (mPhaseBeeCount == 0)
		{
			mPhaseTimer = 0.0f;
			mPhaseMove = true;

		}

		

		if (mPhaseBeeCount == 0 && mPhaseTimer >= 4.0f)
		{
			mPhaseMove = false;
			mOneCount = false;
			mBeeHiveState = eBeeHiveState::Broken;
			mPhaseTimer = 0.0f;
		}
	}

	void BeeHive::SpawnBees(eBeeState beeState)
	{
		Bee* beeObj = object::Instantiate<Bee>(eLayerType::Monster);
		beeObj->SetBeeState(beeState);


	
	}


	void BeeHive::Broken()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Broken", false);
			mOneCount = true;
		}

		float speed = 0.2f;
		mPosition.y -= speed * Time::DeltaTime();

		if (mPhaseTimer >= 1.5f)
		{
			Death();
		}
	}

}