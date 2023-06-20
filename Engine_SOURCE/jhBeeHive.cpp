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
		, mSpawnedBees(0)
		, mDeadBees(0)
		, mSpawnCycle(0)
		, mBeeHiveState(eBeeHiveState::SpawnBees)
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.1f, 0.1f));

		mTransform->SetScale(Vector3(0.5f, 0.5f, 1.0f));

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

		switch (mBeeHiveState)
		{
		case jh::eBeeHiveState::Idle:
			Idle();
			break;
		case jh::eBeeHiveState::SpawnBees:
			SpawnBees();
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
			mAnimator->Play(L"Buzzing", false);
			mOneCount == true;
		}
		if (mDeadBees >= 4) 
		{
			mDeadBees = 0;
			mBeeHiveState = eBeeHiveState::SpawnBees;
			mOneCount = false;
		}
	}

	void BeeHive::SpawnBees()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Buzzing", true);
			mOneCount == true;

		}

		if (mSpawnCycle >= 4)  
		{
			mBeeHiveState = eBeeHiveState::Broken;
			mOneCount = false;
			return;
		}

		mSpawnTimer += Time::DeltaTime(); 

		if (mSpawnTimer >= 1.0f)
		{
			mSpawnTimer = 0.0f;
		/*	Bee* beeObj = object::Instantiate<Bee>(eLayerType::Monster);
			beeObj->SetPosition(Vector3(-0.2f, 0.2f, 1.7f));*/
			mSpawnedBees++;
		}

		if (mSpawnedBees >= 4) 
		{
			mSpawnedBees = 0;
			mBeeHiveState = eBeeHiveState::Idle;
			mOneCount = false;
			mSpawnCycle++;
		}
	}

	void BeeHive::Broken()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Broken", false);
			mOneCount == true;
		}
	}

}