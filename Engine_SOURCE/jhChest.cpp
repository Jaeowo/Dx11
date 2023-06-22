#include "jhChest.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhAnimator.h"
#include "jhChestScript.h"
#include "jhTime.h"
#include "jhPlayerManager.h"
#include "jhPlayer.h"
#include "jhCoin.h"
#include "jhObject.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"

namespace jh
{
	Chest::Chest()
		: mOpen(false)
		, mOneCount(false)
		, mPosition(Vector3(0.0f, 0.0f, 0.0f))
		, mElpasedTime(0.0f)
		, mIsOpen2Played(false)
		, mIsOpenFinishPlayed(false)
		, mChestState(eChestState::Idle)
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mTransform->SetScale(Vector3(0.3f, 0.3f, 1.0f));
		mTransform->SetPosition(mPosition);

		

		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.1f, 0.1f));

		SpriteRenderer* chestsr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> chestmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> chestmaterial = Resources::Find<Material>(L"Chestmaterial");
		chestsr->SetMaterial(chestmaterial);
		chestsr->SetMesh(chestmesh);

		std::shared_ptr<Texture> chesttexture = Resources::Load<Texture>(L"Chest", L"spr_TreasureChest_64x64.png");
		mAnimator->Create(L"Idle", chesttexture, Vector2(64.0f, 64.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 1, 0.15f);
		mAnimator->Create(L"Open1", chesttexture, Vector2(0.0f, 192.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 3, 0.15f);
		mAnimator->Create(L"Open2", chesttexture, Vector2(0.0f, 256.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 3, 0.15f);
		mAnimator->Create(L"OpenFinish", chesttexture, Vector2(0.0f, 320.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 1, 0.15f);
		mAnimator->Create(L"Hanging", chesttexture, Vector2(0.0f, 384.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 1, 0.15f);

		mAnimator->Play(L"Idle", false);

	}
	Chest::~Chest()
	{
	}
	void Chest::Initalize()
	{
		AddComponent<ChestScript>();
	
		mPlayerTransform = PlayerManager::GetPlayer()->getTransform();
		GameObject::Initalize();
	}
	void Chest::Update()
	{
		GameObject::Update();

		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);

		mPlayerPosition = PlayerManager::GetPlayer()->GetPlayerPos();

		if (mOpen == true)
		{
			mChestState = eChestState::Open;
		}
		else
		{

		}

		if (mChestState != eChestState::Hanging && mTransform->GetParent() != nullptr)
		{
			mTransform->SetParent(nullptr);
		}

		switch (mChestState)
		{
		case jh::eChestState::Idle:
			Idle();
			break;
		case jh::eChestState::Open:
			Open();
			break;
		case jh::eChestState::Hanging:
			Hanging();
			break;
		case jh::eChestState::Finish:
			Finish();
			break;
		default:
			break;
		}

	}
	void Chest::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Chest::Render()
	{
		GameObject::Render();
	}

	void Chest::PlayOpen2Animation()
	{
		mAnimator->Play(L"Open2", false);
		mChestState = eChestState::Finish; 
	}

	void Chest::PlayFinishAnimation()
	{
		mAnimator->Play(L"OpenFinish", false);
		mChestState = eChestState::Idle;
	}

	void Chest::SpawnCoin(int coinCount)
	{
		for (int i = 0; i < coinCount; ++i)
		{
			Coin* coin = object::Instantiate<Coin>(eLayerType::BackGrouncObj);

			Vector3 chestPos = mTransform->GetPosition();
			coin->SetPosition(Vector3(chestPos.x, chestPos.y, 1.7f));

			float randomX = (((float)rand() / (RAND_MAX)) - 0.5f) / 2.0f;
			Vector3 direction(randomX, 1.0f, 0.0f);

			// Fire the coin in the direction
			coin->Move(direction);
		}
	}

	void Chest::Idle()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Idle", false);
			mOneCount = true;
		}
	}
	void Chest::Open()
	{

		mElpasedTime += Time::DeltaTime();

		if (mElpasedTime >= 0.5f && mElpasedTime < 2.0f && !mIsOpen2Played)
		{
			SpawnCoin(5);
			mAnimator->Play(L"Open2", false);
			mIsOpen2Played = true;

			std::shared_ptr<AudioClip> audioClip = Resources::Load<AudioClip>
				(L"Open", L"..\\Resources\\Audio\\unlockTeleporter.wav");

			AudioSource* audioSource = AddComponent<AudioSource>();
			audioSource->SetClip(audioClip);
			audioSource->SetLoop(false);


			audioSource->Play();
		}
		else if (mElpasedTime >= 2.0f && !mIsOpenFinishPlayed) 
		{
			mAnimator->Play(L"OpenFinish", false);
			mIsOpenFinishPlayed = true;
			mChestState = eChestState::Finish;
		}


	}
	void Chest::Hanging()
	{
		if (mOneCount == false)
		{
			//mTransform->SetParent(mPlayerTransform);
			//mPosition = (Vector3(0.0f, 0.0f, 1.0f));
			//mTransform->SetScale(Vector3(0.9f, 0.9f, 1.0f));
			//mAnimator->Play(L"Hanging", false);
			//mOneCount = true;
		}
	}
	void Chest::Finish()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"OpenFinish", false);
			mOneCount = true;
		}
	}
}