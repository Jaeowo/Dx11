#include "jhBeeHive.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhObject.h"
#include "jhAnimator.h"
#include "jhPlayer.h"
#include "jhPlayerManager.h"
#include "jhTime.h"

namespace jh
{
	BeeHive::BeeHive()
		: mPosition(Vector3(0.0f, 0.0f, 0.0f))
		, mOneCount(false)
		, mTotalTime(0.0f)
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
			mOneCount == true;
		}
	}

	void BeeHive::SpawnBees()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Buzzing", true);
			mOneCount == true;
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