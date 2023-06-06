#include "jhTortoise.h"
#include "jhAnimator.h"
#include "jhResources.h"
#include "jhSpriteRenderer.h"
#include "jhTortoiseBullet.h"
#include "jhObject.h"

namespace jh
{
	Tortoise::Tortoise()
		: mTortoiseState(eTortoiseState::Idle)
		, mMonsterPosition(Vector3(0.0f, 0.0f, 0.0f))
		, mHp(50)
		, mCount(0)
		, mTarget(false)
		, mElapsedTime(0.0f)
		, mCheck(false)
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mTransform->SetScale(Vector3(0.3f, 0.3f, 1.0f));
		mTransform->SetPosition(mMonsterPosition);

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
	}	
	Tortoise::~Tortoise()
	{
	}
	void Tortoise::Initalize()
	{
		GameObject::Initalize();

	}
	void Tortoise::Update()
	{
		GameObject::Update();

		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mMonsterPosition);

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
		case jh::eTortoiseState::FindMask:
			FindMask();
			break;
		case jh::eTortoiseState::Turn:
			Turn();
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
		if (mCheck == false)
		{
			mAnimator->Play(L"IdleMask", true);
			mCheck = true;
		}
	}
	void Tortoise::MaskJump()
	{
		if (mCheck == false)
		{
			mAnimator->Play(L"Jump", false);
			mCheck = true;
		}
	}
	void Tortoise::MaskMove()
	{
		if (mCheck == false)
		{
			mAnimator->Play(L"Move", true);
			mCheck = true;
		}
	}
	void Tortoise::MaskTurn()
	{
		if (mCheck == false)
		{
			mAnimator->Play(L"TurnMask", false);
			mCheck = true;
		}
	}
	void Tortoise::MaskShoot()
	{
		if (mCheck == false)
		{
			mAnimator->Play(L"MoveShoot", false);
			//TortoiseBullet* tortoisebullet = object::Instantiate<TortoiseBullet>(eLayerType::MonsterObject);
			mCheck = true;
			
		}
	}
	void Tortoise::Idle()
	{
		if (mCheck == false)
		{
			mAnimator->Play(L"IdleNoMask", true);
			mCheck = true;
		}
	}
	void Tortoise::Hit()
	{
		if (mCheck == false)
		{
			mAnimator->Play(L"Hit", false);
			mCheck = true;
		}
	}
	void Tortoise::Move()
	{
		if (mCheck == false)
		{
			mAnimator->Play(L"MoveNomask", true);
			mCheck = true;
		}
	}
	void Tortoise::EquipMask()
	{
		if (mCheck == false)
		{
			mAnimator->Play(L"EquipMask", false);
			mCheck = true;
		}
	}
	void Tortoise::Fly()
	{
		if (mCheck == false)
		{
			mAnimator->Play(L"FlyNomask", true);
			mCheck = true;
		}
	}
	void Tortoise::FlyHit()
	{
		if (mCheck == false)
		{
			mAnimator->Play(L"FlyHit", false);
			mCheck = true;
		}
	}
	void Tortoise::FlyDeath()
	{
		if (mCheck == false)
		{
			mAnimator->Play(L"FlyDeath", false);
			mCheck = true;
		}
	}
	void Tortoise::FlyEquipMask()
	{
		if (mCheck == false)
		{
			mAnimator->Play(L"FlyEquipMask", false);
			mCheck = true;
		}
	}
	void Tortoise::FindMask()
	{
		if (mCheck == false)
		{
			mAnimator->Play(L"MoveNomask", true);
			mCheck = true;
		}
	}
	void Tortoise::Turn()
	{
		if (mCheck == false)
		{
			mAnimator->Play(L"TurnNomask", false);
			mCheck = true;
		}
	}
	void Tortoise::MaskSpawnWing()
	{
		if (mCheck == false)
		{
			mAnimator->Play(L"SpawnWings", false);
			mCheck = true;
		}
	}
	void Tortoise::MaskFly()
	{
		if (mCheck == false)
		{
			mAnimator->Play(L"Fly", true);
			mCheck = true;
		}
	}
	void Tortoise::MaskFlyShoot()
	{
		if (mCheck == false)
		{
			mAnimator->Play(L"FlyShoot", false);
			mCheck = true;
		}
	}
}