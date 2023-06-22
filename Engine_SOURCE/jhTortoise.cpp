#include "jhTortoise.h"
#include "jhAnimator.h"
#include "jhResources.h"
#include "jhSpriteRenderer.h"
#include "jhTortoiseBullet.h"
#include "jhObject.h"
#include "jhInput.h"
#include "jhCollider2D.h"
#include "jhTime.h"
#include "jhPlayerManager.h"
#include "jhPlayer.h"
#include "jhTortoiseScript.h"
#include "jhTortoiseMask.h"
#include "jhJungleDoor.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"
#include "jhBigDustEffect.h"

namespace jh
{
	Tortoise::Tortoise()
		: mTortoiseState(eTortoiseState::MaskIdle)
		, mMonsterPosition(Vector3(0.0f, 0.0f, 0.0f))
		, mHp(30)
		, mCount(0)
		, mTarget(false)
		, mElapsedTime(0.0f)
		, mAniCheck(false)
		, mStartTrigger(false)
		, mFunctionCheck(false)
		, mMaskOn(true)
		, mIsFlying(false)
		, mIgnoreCollisionTime(0.0f)
		, mEventOn(false)

	{

		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mTransform->SetScale(Vector3(0.3f, 0.3f, 1.0f));
		mTransform->SetPosition(mMonsterPosition);
		mRotation = (Vector3(0.0f, 180.0f, 0.0f));

		mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.25f, 0.28f));

		SpriteRenderer* tortoisesr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> tortoisemesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> tortoisematerial = Resources::Find<Material>(L"TortoiseMaterial");
		tortoisesr->SetMaterial(tortoisematerial);
		tortoisesr->SetMesh(tortoisemesh);
	
		std::shared_ptr<Texture> tortoisetexture = Resources::Load<Texture>(L"IdleMask", L"Masked Tortoise\\idleMask.png");
		std::shared_ptr<Texture> tortoisetexture2 = Resources::Load<Texture>(L"IdleNoMask", L"Masked Tortoise\\idleNoMask.png");
		std::shared_ptr<Texture> tortoisetexture3 = Resources::Load<Texture>(L"EquipMask", L"Masked Tortoise\\sprEquipMask_strip8.png");
		std::shared_ptr<Texture> tortoisetexture4 = Resources::Load<Texture>(L"Fly", L"Masked Tortoise\\sprFly_strip8.png");
		std::shared_ptr<Texture> tortoisetexture5 = Resources::Load<Texture>(L"FlyDeath", L"Masked Tortoise\\sprFlyDeath.png");
		std::shared_ptr<Texture> tortoisetexture6 = Resources::Load<Texture>(L"FlyEquipMask", L"Masked Tortoise\\sprFlyEquipMask_strip8.png");
		std::shared_ptr<Texture> tortoisetexture7 = Resources::Load<Texture>(L"FlyHit", L"Masked Tortoise\\sprFlyHit_strip3.png");
		std::shared_ptr<Texture> tortoisetexture8 = Resources::Load<Texture>(L"FlyNomask", L"Masked Tortoise\\sprFlyNoMask_strip8.png");
		std::shared_ptr<Texture> tortoisetexture9 = Resources::Load<Texture>(L"FlyShoot", L"Masked Tortoise\\sprFlyShoot_strip8.png");
		std::shared_ptr<Texture> tortoisetexture10 = Resources::Load<Texture>(L"Hit", L"Masked Tortoise\\sprHit_strip3.png");
		std::shared_ptr<Texture> tortoisetexture11 = Resources::Load<Texture>(L"Jump", L"Masked Tortoise\\sprJump_strip2.png");
		std::shared_ptr<Texture> tortoisetexture12 = Resources::Load<Texture>(L"LightUp", L"Masked Tortoise\\sprLightup_strip5.png");
		std::shared_ptr<Texture> tortoisetexture13 = Resources::Load<Texture>(L"Move", L"Masked Tortoise\\sprMove_strip8.png");
		std::shared_ptr<Texture> tortoisetexture14 = Resources::Load<Texture>(L"MoveNomask", L"Masked Tortoise\\sprMoveNoMask_strip8.png");
		std::shared_ptr<Texture> tortoisetexture15 = Resources::Load<Texture>(L"MoveShoot", L"Masked Tortoise\\sprMoveShoot_strip8.png");
		std::shared_ptr<Texture> tortoisetexture16 = Resources::Load<Texture>(L"SpawnWings", L"Masked Tortoise\\sprSpawnWings_strip7.png");
		std::shared_ptr<Texture> tortoisetexture17 = Resources::Load<Texture>(L"TurnMask", L"Masked Tortoise\\turnMask_strip5.png");
		std::shared_ptr<Texture> tortoisetexture18 = Resources::Load<Texture>(L"TurnNomask", L"Masked Tortoise\\turnNoMask_strip5.png");

		mAnimator->Create(L"IdleMask", tortoisetexture, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"IdleNoMask", tortoisetexture2, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"EquipMask", tortoisetexture3, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 8, 0.2f);
		mAnimator->Create(L"Fly", tortoisetexture4, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 8, 0.2f);
		mAnimator->Create(L"FlyDeath", tortoisetexture5, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"FlyEquipMask", tortoisetexture6, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 8, 0.2f);
		mAnimator->Create(L"FlyHit", tortoisetexture7, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 3, 0.2f);
		mAnimator->Create(L"FlyNomask", tortoisetexture8, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 8, 0.2f);
		mAnimator->Create(L"FlyShoot", tortoisetexture9, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 8, 0.2f);
		mAnimator->Create(L"Hit", tortoisetexture10, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 3, 0.2f);
		mAnimator->Create(L"Jump", tortoisetexture11, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 2, 0.2f);
		mAnimator->Create(L"LightUp", tortoisetexture12, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 5, 0.2f);
		mAnimator->Create(L"Move", tortoisetexture13, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 8, 0.2f);
		mAnimator->Create(L"MoveNomask", tortoisetexture14, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 8, 0.2f);
		mAnimator->Create(L"MoveShoot", tortoisetexture15, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 8, 0.2f);
		mAnimator->Create(L"SpawnWings", tortoisetexture16, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 7, 0.2f);
		mAnimator->Create(L"TurnMask", tortoisetexture17, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 5, 0.2f);
		mAnimator->Create(L"TurnNomask", tortoisetexture18, Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 5, 0.2f);

		mAnimator->Play(L"IdleMask", true);

		std::shared_ptr<AudioClip> flash = std::make_shared<AudioClip>();
		flash->Load(L"..\\Resources\\Audio\\flash.wav");
		Resources::Insert<AudioClip>(L"Flash", flash);

		

	
	}	
	Tortoise::~Tortoise()
	{
	}
	void Tortoise::Initalize()
	{	
		GameObject::Initalize();
		AddComponent<TortoiseScript>();

	}
	void Tortoise::Update()
	{
		GameObject::Update();

		if (mHp == 15 &&
			mTortoiseState == eTortoiseState::MaskMove)
		{
			mAniCheck = false;
			mTortoiseState = eTortoiseState::MaskSpawnWing;
		}

		if (mHp <= 0 &&
			mTortoiseState == eTortoiseState::Fly)
		{
			mAniCheck = false;
			mTortoiseState = eTortoiseState::FlyDeath;
		}

		mTransform = GetComponent<Transform>();

		mTargetPosition = PlayerManager::GetPlayer()->GetPlayerPos();
		mTransform->SetPosition(mMonsterPosition);

		mTransform->SetRotation(mRotation);

		mElapsedTime += Time::DeltaTime();

		if (mIgnoreCollisionTime > 0.0f) 
		{
			mIgnoreCollisionTime -= Time::DeltaTime();
		}
		switch (mTortoiseState)
		{
		case jh::eTortoiseState::MaskIdle:
			MaskIdle();
			break;
		case jh::eTortoiseState::MaskJump:
			MaskJump();
			break;
		case jh::eTortoiseState::MaskMove:
			MaskMove();
			break;
		case jh::eTortoiseState::MaskTurn:
			MaskTurn();
			break;
		case jh::eTortoiseState::MaskShoot:
			MaskShoot();
			break;
		case jh::eTortoiseState::MaskFlyShoot:
			MaskFlyShoot();
			break;
		case jh::eTortoiseState::RemoveMask:
			RemoveMask();
			break;
		case jh::eTortoiseState::RemoveFlyMask:
			RemoveFlyMask();
			break;
		case jh::eTortoiseState::MaskSpawnWing:
			MaskSpawnWing();
			break;
		case jh::eTortoiseState::MaskFly:
			MaskFly();
			break;
		case jh::eTortoiseState::Idle:
			Idle();
			break;
		case jh::eTortoiseState::Hit:
			Hit();
			break;
		case jh::eTortoiseState::Move:
			Move();
			break;
		case jh::eTortoiseState::EquipMask:
			EquipMask();
			break;
		case jh::eTortoiseState::Fly:
			Fly();
			break;
		case jh::eTortoiseState::FlyHit:
			FlyHit();
			break;
		case jh::eTortoiseState::FlyDeath:
			FlyDeath();
			break;
		case jh::eTortoiseState::FlyEquipMask:
			FlyEquipMask();
			break;
		case jh::eTortoiseState::Turn:
			Turn();
			break;
		case jh::eTortoiseState::Jump:
			Jump();
			break;
		default:
			break;
		}

	}
	void Tortoise::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Tortoise::Render()
	{
		GameObject::Render();
	}
	void Tortoise::MaskIdle()
	{
		if (mAniCheck == false)
		{
			mAnimator->Play(L"IdleMask", true);
			mAniCheck = true;
		}
	}
	void Tortoise::MaskJump()
	{
		if (mAniCheck == false)
		{
			mAnimator->Play(L"Jump", false);
			mAniCheck = true;
		}
	}
	void Tortoise::MaskMove()
	{
		if (mAniCheck == false) 
		{
			mAnimator->Play(L"Move", true);
			mEventOn = false;
			mAniCheck = true;
			mFunctionCheck = false;
		}

		if (mIgnoreCollisionTime > 0.0f)
		{
			mIgnoreCollisionTime -= Time::DeltaTime();
		}

		if (mRotation.y >= 180.0f) 
		{
			mMonsterPosition.x -= 0.1f * Time::DeltaTime();
		}
		else 
		{
			mMonsterPosition.x += 0.1f * Time::DeltaTime();
		}

		if (!mFunctionCheck)
		{
			static float time = 0.0f;
			time += Time::DeltaTime();
			if (time >= 2.0f)
			{
				mTortoiseState = eTortoiseState::MaskShoot;
				mFunctionCheck = false;
				time = 0.0f;
			}
		}

	}
	void Tortoise::MaskTurn()
	{
		if (mAniCheck == false) {
			mAnimator->Play(L"TurnMask", false);
			mAniCheck = true;
		}
		if (mRotation.y >= 180.0f) {
			mRotation.y = 0.0f;
			mAniCheck = false;
			mIgnoreCollisionTime = 0.1f; 
			mTortoiseState = eTortoiseState::MaskMove;
		}
		else {
			mRotation.y = 180.0f;
			mAniCheck = false;
			mIgnoreCollisionTime = 0.1f;
			mTortoiseState = eTortoiseState::MaskMove;
		}
	}
	void Tortoise::MaskShoot()
	{
		if (mAniCheck == false)
		{
			mAnimator->Play(L"MoveShoot", true);
			mAniCheck = true;
		}

		if (mRotation.y >= 180.0f)
		{
			mMonsterPosition.x -= 0.1f * Time::DeltaTime();
		}
		else
		{
			mMonsterPosition.x += 0.1f * Time::DeltaTime();
		}

		if (!mFunctionCheck)
		{
			static float time = 0.0f;
			time += Time::DeltaTime();

			static int bulletCount = 0;  

			if (time >= 0.3f && bulletCount < 5)  
			{
				TortoiseBullet* tortoisebullet = object::Instantiate<TortoiseBullet>(eLayerType::MonsterObject);
				tortoisebullet->SetPosition(mMonsterPosition);

				time = 0.0f;
				bulletCount++;

				if (bulletCount >= 5)
				{
					mFunctionCheck = true;
					mTortoiseState = eTortoiseState::MaskMove;
					mAniCheck = false;
					bulletCount = 0;
				}
			}
		}

		


	}
	void Tortoise::Idle()
	{
		if (mAniCheck == false)
		{
			mAnimator->Play(L"IdleNoMask", true);
			mAniCheck = true;
		}
	}
	void Tortoise::Hit()
	{
		if (mAniCheck == false)
		{
			mAnimator->Play(L"Hit", false);
			mElapsedTime = 0.0f;
			mAniCheck = true;
		}

		if (mElapsedTime >= 0.2f)
		{
			mAniCheck = false;
			mTortoiseState = eTortoiseState::Move;
		}

		if (!mEventOn && (mHp == 25 || mHp == 20 || mHp == 15))
		{
			mEventOn = true;
			mAniCheck = false;
			mTortoiseState = eTortoiseState::Move;
		}

	}
	void Tortoise::Move()
	{
		if (mAniCheck == false)
		{
			mAnimator->Play(L"MoveNomask", true);
			mAniCheck = true;
		}

		if (mtortoisemask != nullptr)
		{
			Vector3 mMaskPos = mtortoisemask->GetPosition();
			float speed = 0.1f;

			Vector3 Dir = mMaskPos - mMonsterPosition;
			Dir.Normalize();
			mMonsterPosition.x += Dir.x * speed * Time::DeltaTime();

			if (mMaskPos.x < mMonsterPosition.x)
			{
				mRotation.y = 180.0f;
			}
			else
			{
				mRotation.y = 0.0f;
			}

		}

	
	}
	void Tortoise::EquipMask()
	{
		if (mAniCheck == false)
		{
			mElapsedTime = 0.0f;
			mAnimator->Play(L"EquipMask", false);
			mAniCheck = true;
			if (mtortoisemask != nullptr)
			{
				mtortoisemask->Death();
			}
		}
		if (mElapsedTime >= 0.3f)
		{
			mAniCheck = false;
			mTortoiseState = eTortoiseState::MaskMove;
		}
	}
	void Tortoise::Fly()
	{
		if (mAniCheck == false)
		{
			mAnimator->Play(L"FlyNomask", true);
			mAniCheck = true;
		}

		if (mtortoisemask != nullptr)
		{
			Vector3 mMaskPos = mtortoisemask->GetPosition();
			float speed = 0.1f;
			float yDistance = abs(mMaskPos.y - mMonsterPosition.y);

			Vector3 Dir = mMaskPos - mMonsterPosition;
			Dir.Normalize();
			mMonsterPosition += Dir * speed * Time::DeltaTime();

			if (mMaskPos.x < mMonsterPosition.x)
			{
				mRotation.y = 180.0f;
			}
			else
			{
				mRotation.y = 0.0f;
			}
		}

	
	}
	void Tortoise::FlyHit()
	{
		if (mAniCheck == false)
		{
			mAnimator->Play(L"FlyHit", false);
			mElapsedTime = 0.0f;
			mAniCheck = true;
		}
		if (mElapsedTime >= 0.2f)
		{
			mAniCheck = false;
			mTortoiseState = eTortoiseState::Fly;
		}

		if (!mEventOn && (mHp == 10 || mHp == 5 ))
		{
			mEventOn = true;
			mAniCheck = false;
			mTortoiseState = eTortoiseState::Fly;
		}

		
	}
	void Tortoise::FlyDeath()
	{
		if (mAniCheck == false)
		{
			mElapsedTime = 0.0f;
			mAnimator->Play(L"FlyDeath", false);
			BigDustEffect* bigdusteffect = object::Instantiate<BigDustEffect>(eLayerType::Effect);
			bigdusteffect->SetPosition(mMonsterPosition);

			JungleDoor* jungledoor = object::Instantiate<JungleDoor>(eLayerType::BackGround);
			jungledoor->SetCavetoCave2(true);
			jungledoor->SetPosition(Vector3(-1.53f, -2.55f, 1.7f));
			mAniCheck = true;
		}

		float speed = 0.11f;  
		mMonsterPosition.y -= speed * Time::DeltaTime();

		if (mElapsedTime >= 1.5f)
		{
			Death();
		}
	}
	void Tortoise::FlyEquipMask()
	{
		if (mAniCheck == false)
		{
			mElapsedTime = 0.0f;
			mAnimator->Play(L"FlyEquipMask", false);
			mAniCheck = true;
			if (mtortoisemask != nullptr)
			{
				mtortoisemask->Death();
			}
		}

		if (mElapsedTime >= 0.3f)
		{
			mAniCheck = false;
			mTortoiseState = eTortoiseState::MaskFly;
		}
	}
	void Tortoise::Jump()
	{

	}
	void Tortoise::Turn()
	{
		if (mAniCheck == false)
		{
			mAnimator->Play(L"TurnNomask", false);
			mAniCheck = true;
		}
		if (mRotation.y >= 180.0f)
		{
			mRotation.y = 0.0f;
			mAniCheck = false;
			mTortoiseState = eTortoiseState::MaskMove;
		}
		else
		{
			mRotation.y = 180.0f;
			mAniCheck = false;
			mTortoiseState = eTortoiseState::MaskMove;
		}
	}
	void Tortoise::FlyBase()
	{
		float speed = 0.1f;

		float yDistance = abs(mTargetPosition.y - mMonsterPosition.y);

		Vector3 Dir = mTargetPosition - mMonsterPosition;
		Dir.Normalize();
		mMonsterPosition += Dir * speed * Time::DeltaTime();

		if (mTargetPosition.x < mMonsterPosition.x)
		{
			mRotation.y = 180.0f;
		}
		else
		{
			mRotation.y = 0.0f;
		}
	}
	void Tortoise::MaskSpawnWing()
	{

		if (mAniCheck == false)
		{
			mAnimator->Play(L"SpawnWings", false);
			std::shared_ptr<AudioClip> flash = Resources::Find<AudioClip>(L"Flash");
			flash->Play();
			mAniCheck = true;

			mElapsedTime = 0.0f;
		}

		if (mElapsedTime >= 0.9f)
		{
			mTortoiseState = eTortoiseState::MaskFly;
			mIsFlying = true;
			mAniCheck = false;
		}
	}
	void Tortoise::MaskFly()
	{
		if (mAniCheck == false)
		{
			mAnimator->Play(L"Fly", true);
			mEventOn = false;
			mAniCheck = true;
			mFunctionCheck = false;
		}
		
		FlyBase();

		if (!mFunctionCheck)
		{
			static float time = 0.0f;
			time += Time::DeltaTime();
			if (time >= 2.0f)
			{
				mTortoiseState = eTortoiseState::MaskFlyShoot;
				mFunctionCheck = false;
				time = 0.0f;
			}
		}

	}
	void Tortoise::MaskFlyShoot()
	{
		if (mAniCheck == false)
		{
			mAnimator->Play(L"FlyShoot", false);
			mAniCheck = true;
		}
		
		FlyBase();

		if (!mFunctionCheck)
		{
			static float time = 0.0f;
			time += Time::DeltaTime();

			static int bulletCount = 0;

			if (time >= 0.3f && bulletCount < 5)
			{
				TortoiseBullet* tortoisebullet = object::Instantiate<TortoiseBullet>(eLayerType::MonsterObject);
				tortoisebullet->SetPosition(mMonsterPosition);

				time = 0.0f;
				bulletCount++;

				if (bulletCount >= 5)
				{
					mFunctionCheck = true;
					mTortoiseState = eTortoiseState::MaskFly;
					mAniCheck = false;
					bulletCount = 0;
				}
			}
		}
	}
	void Tortoise::RemoveMask()
	{
		if (mAniCheck == false)
		{
			mtortoisemask = object::Instantiate<TortoiseMask>(eLayerType::MonsterObject);
			mtortoisemask->SetPosition(mMonsterPosition);
			mAnimator->Play(L"Hit", false);
			mElapsedTime = 0.0f;

			if (mRotation.y >= 180.0f)
			{
				mtortoisemask->SetLeft(true);
			}
			else
			{
				mtortoisemask->SetRight(true);
			}

			mAniCheck = true;
		}

		if (mElapsedTime >= 0.5f)
		{
			mTortoiseState = eTortoiseState::Move;
			mAniCheck = false;
		}
		
	}
	void Tortoise::RemoveFlyMask()
	{
		if (mAniCheck == false)
		{
			mtortoisemask = object::Instantiate<TortoiseMask>(eLayerType::MonsterObject);
			mtortoisemask->SetPosition(mMonsterPosition);
			mAnimator->Play(L"FlyHit", false);
			mElapsedTime = 0.0f;

			if (mRotation.y >= 180.0f)
			{
				mtortoisemask->SetLeft(true);
			}
			else
			{
				mtortoisemask->SetRight(true);
			}
			mAniCheck = true;
		}

		if (mElapsedTime >= 0.5f)
		{
			mTortoiseState = eTortoiseState::Fly;
			mAniCheck = false;
		}

	}
}