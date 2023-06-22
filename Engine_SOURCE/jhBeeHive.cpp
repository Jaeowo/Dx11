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
#include "jhPhase1.h"
#include "jhPhase2.h"
#include "jhPhase3.h"
#include "jhPhase4.h"
#include "jhBigDustEffect.h"

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

		mSpawnTimer += Time::DeltaTime();
		mPhaseTimer += Time::DeltaTime();

		switch (mBeeHiveState)
		{
		case jh::eBeeHiveState::Idle:
			Idle();
			break;
		case eBeeHiveState::Phase1:
			p1();
			break;
		case eBeeHiveState::Phase2:
			p2();
			break;
		case eBeeHiveState::Phase3:
			p3();
			break;
		case eBeeHiveState::Phase4:
			p4();
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


	void BeeHive::p1()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Buzzing", false);
			mphase1 = object::Instantiate<Phase1>(eLayerType::UI);
			mOneCount = true;
		}
		if (mphase1->GetClear() == true)
		{
			mBeeHiveState = eBeeHiveState::Phase2;
			mOneCount = false;
		}

	}


	void BeeHive::p2()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Buzzing", false);
			mphase2 = object::Instantiate<Phase2>(eLayerType::UI);
			mOneCount = true;
		}
		if (mphase2->GetClear() == true)
		{
			mBeeHiveState = eBeeHiveState::Phase3;
			mOneCount = false;
		}
	}

	void BeeHive::p3()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Buzzing", false);
			mphase3 = object::Instantiate<Phase3>(eLayerType::UI);
			mOneCount = true;
		}
		if (mphase3->GetClear() == true)
		{
			mBeeHiveState = eBeeHiveState::Phase4;
			mOneCount = false;
		}
	}

	void BeeHive::p4()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Buzzing", false);
			mphase4 = object::Instantiate<Phase4>(eLayerType::UI);
			mOneCount = true;
		}
		if (mphase4->GetClear() == true)
		{
			mBeeHiveState = eBeeHiveState::Broken;
			mOneCount = false;
		}
	}



	void BeeHive::Broken()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Broken", false);
			mOneCount = true;
			BigDustEffect* bigdusteffect = object::Instantiate<BigDustEffect>(eLayerType::Effect);
			bigdusteffect->SetPosition(mPosition);

			mPhaseTimer = 0.0f;
		}

		float speed = 0.1f;
		mPosition.y -= speed * Time::DeltaTime();

		if (mPhaseTimer >= 1.5f)
		{
			Death();
		}

	}

}