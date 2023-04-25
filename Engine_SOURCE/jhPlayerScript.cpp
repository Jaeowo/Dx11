#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhAnimator.h"
#include "jhPlayerManager.h"
#include "jhPlayer.h"
#include "jhResources.h"
#include "jhRigidbody.h"
#include "jhGeddy.h"

namespace jh
{
	PlayerScript::PlayerScript()
		:Script()
		, mPlayerState(ePlayerState::Idle)
		, mbGround(true)
		, mbCarrying(false)
		, mCount(0)
		, mTime(0.0f)
		, mSpeed(0.5f)
		, mFallingTime(0.0f)
		, mIsFlying(false)
	{

		mVelocity = (Vector2(0.0f, 0.0f));
		mMass = 150.0f;

		mGravity = 0.00005f;
	
		Animator* mAnimator = PlayerManager::GetPlayer()->AddComponent<Animator>();


		std::shared_ptr<Texture> herotexture = Resources::Load<Texture>(L"hero", L"Otus\\hero.png");
		std::shared_ptr<Texture> hero2texture = Resources::Load<Texture>(L"hero2", L"Otus\\hero2.png");
		std::shared_ptr<Texture> flyUpStartCarrytexture = Resources::Load<Texture>(L"FlyUpStartCarry", L"Otus\\flyUpStartCarry_strip8.png");
		std::shared_ptr<Texture> FlyGrabtexture = Resources::Load<Texture>(L"FlyGrab", L"Otus\\sprFlyGrab_strip11.png");
		std::shared_ptr<Texture> SpreadWingstexture = Resources::Load<Texture>(L"SpreadWings", L"Otus\\sprOtusSpreadWings_112x96_strip9.png");
		std::shared_ptr<Texture> EnterDoortexture = Resources::Load<Texture>(L"EnterDoor", L"Otus\\sprOtusEnterDoor_112x96_strip13.png");
		std::shared_ptr<Texture> Dietexture = Resources::Load<Texture>(L"Die", L"Otus\\sprOtusDie_112x96_strip12.png");
		std::shared_ptr<Texture> Eattexture = Resources::Load<Texture>(L"Eat", L"Otus\\eat_strip14.png");
		std::shared_ptr<Texture> Flystarttexture = Resources::Load<Texture>(L"FlyStart", L"Otus\\flyUpStart_strip8.png");
		std::shared_ptr<Texture> FlyStartRolltexture = Resources::Load<Texture>(L"FlyStartRoll", L"Otus\\roll_strip8.png");
		std::shared_ptr<Texture> FlyRolltexture = Resources::Load<Texture>(L"FlyRoll", L"Otus\\roll_strip9.png");
		std::shared_ptr<Texture> GroundRolltexture = Resources::Load<Texture>(L"GroundRoll", L"Otus\\rollGround_strip6.png");


		mAnimator->Create(L"Idle", herotexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 13, 0.25f);
		mAnimator->Create(L"MoveRight", herotexture, Vector2(0.0f, 96.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 12, 0.2f);
		mAnimator->Create(L"Flying", herotexture, Vector2(0.0f, 192.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 11, 0.2f);
		mAnimator->Create(L"Jump", herotexture, Vector2(0.0f, 384.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 3, 0.2f);
		mAnimator->Create(L"JumpDown", herotexture, Vector2(0.0f, 480.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 5, 0.2f);
		mAnimator->Create(L"hurt", hero2texture, Vector2(0.0f, 288.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"flyinghurt", hero2texture, Vector2(0.0f, 384.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"StartAttack", hero2texture, Vector2(0.0f, 1056.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 6, 0.12f);
		mAnimator->Create(L"Attacking", hero2texture, Vector2(0.0f, 1152.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 9, 0.1f);
		mAnimator->Create(L"FlyUpStartCarry", flyUpStartCarrytexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 8, 0.12f);
		mAnimator->Create(L"FlyGrab", FlyGrabtexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 11, 0.15f);
		mAnimator->Create(L"SpreadWings", SpreadWingstexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 9, 0.15f);
		mAnimator->Create(L"EnterDoor", EnterDoortexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 13, 0.15f);
		mAnimator->Create(L"Die", Dietexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 12, 0.15f);
		mAnimator->Create(L"Eat", Eattexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 14, 0.15f);
		mAnimator->Create(L"FlyStart", Flystarttexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 8, 0.15f);
		mAnimator->Create(L"FlyStartRoll", FlyStartRolltexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 8, 0.15f);
		mAnimator->Create(L"FlyRoll", FlyRolltexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 9, 0.15f);
		mAnimator->Create(L"GroundRoll", GroundRolltexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 6, 0.15f);

		
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initalize()
	{
		
	
	}
	void PlayerScript::Update()
	{
	
		mTransform = GetOwner()->GetComponent<Transform>();
		mAnimator = GetOwner()->GetComponent<Animator>();

		
		mPlayerPosition = mTransform->GetPosition();
		mTime += Time::DeltaTime();
		mPlayerState = PlayerManager::GetPlayer()->GetPlayerState();
		PlayerManager::GetPlayer()->SetPlayerPos(mPlayerPosition);

		mCount = PlayerManager::GetPlayer()->GetCount();

#pragma region FALL
		float deltaY = mPlayerPosition.y - mBeforePos.y;

		if (mbGround)
			{
			if (deltaY < 0.0f)
			{
				mFallingTime += Time::DeltaTime();

				if (mFallingTime > 0.1f)
				{	
					if (mPlayerState != ePlayerState::Fall && mIsFlying == false)
					{
						PlayerManager::GetPlayer()->SetCount(0);
						PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::Fall);
					}

					mFallingTime = 0.0f;
	
				}
			}
			else
			{
				mFallingTime = 0.0f;
			}
		}

		mBeforePos = mPlayerPosition;
	
#pragma endregion

		PlayerManager::GetPlayer()->SetIsFly(mIsFlying);

		if (mIsFlying == true)
		{
	
		}
		else
		{
			mPlayerPosition.x += mVelocity.x * (float)Time::DeltaTime();
			mPlayerPosition.y += mVelocity.y + 0.5f * mGravity * (float)Time::DeltaTime() * (float)Time::DeltaTime();
			mVelocity.y -= mGravity * (float)Time::DeltaTime();
			mTransform->SetPosition(mPlayerPosition);

			if (mPlayerState == ePlayerState::Jump)
			{
				mPlayerPosition.x += mVelocity.x * (float)Time::DeltaTime();
				mPlayerPosition.y += mVelocity.y + 0.5f * mGravity * (float)Time::DeltaTime() * (float)Time::DeltaTime();
				mVelocity.y -= mGravity * (float)Time::DeltaTime();
				mTransform->SetPosition(mPlayerPosition);
			}
		}

		if (PlayerManager::GetPlayer()->GetIsGround() == true)
		{
			mGravity = 0.0f;
			mVelocity.y = 0.0f;
		}
		else if (PlayerManager::GetPlayer()->GetIsGround() == false)
		{
			mGravity = 0.00005f;
		}
	
		switch (mPlayerState)
		{
		case jh::enums::ePlayerState::Idle:
			Idle();
			break;
		case jh::enums::ePlayerState::LeftRun:
			LeftRun();
			break;
		case jh::enums::ePlayerState::RightRun:
			RightRun();
			break;
		case jh::enums::ePlayerState::Jump:
			Jump();
			break;
		case jh::enums::ePlayerState::Fall:
			Fall();
			break;
		case jh::enums::ePlayerState::GroundRoll:
			GroundRoll();
			break;
		case jh::enums::ePlayerState::EnterDoor:
			break;
		case jh::enums::ePlayerState::StartAttack:
			break;
		case jh::enums::ePlayerState::Attacking:
			Attacking();
			break;
		case jh::enums::ePlayerState::StartFly:
			StartFly();
			break;
		case jh::enums::ePlayerState::Fly:
			Fly();
			break;
		case jh::enums::ePlayerState::FlyRoll:
			FlyRoll();
			break;
		case jh::enums::ePlayerState::FlyGrab:
			FlyGrab();
			break;
		case jh::enums::ePlayerState::FlyCarry:
			break;
		case jh::enums::ePlayerState::FlyHurt:
			break;
		case jh::enums::ePlayerState::FlyAttack:
			FlyAttack();
			break;
		case jh::enums::ePlayerState::Eat:
			break;
		case jh::enums::ePlayerState::Hurt:
			break;
		case jh::enums::ePlayerState::Die:
			break;
		default:
			break;
		}

		
	}
	void PlayerScript::Render()
	{
	}
	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
	/*	Geddy* geddyObj = dynamic_cast<Geddy*>(collider->GetOwner());
		geddyObj->SetGeddyState(eGeddyState::Hanging);*/
	}
	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void PlayerScript::Idle()
	{
		if (mCount == 0)
		{
			mVelocity.y = 0.0f;

			mIsFlying = false;
			mAnimator->Play(L"Idle", true);
			PlayerManager::GetPlayer()->SetCount(1);
			PlayerManager::GetPlayer()->SetIsFlyDown(false);
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			Vector3 CheckRotation = mTransform->GetRotation();
			if (CheckRotation.y == 180.0f)
			{
				mTransform->SetRotation(Vector3(0.0f, 360.0f, 0.0f));
			}
			PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::RightRun);
			PlayerManager::GetPlayer()->SetCount(0);
			
		}
		if (Input::GetKeyDown(eKeyCode::A))
		{
			PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::LeftRun);
			PlayerManager::GetPlayer()->SetCount(0);
		}
		if (Input::GetKeyDown(eKeyCode::W))
		{
			PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::Jump);
			PlayerManager::GetPlayer()->SetCount(0);
		}
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::GroundRoll);
			PlayerManager::GetPlayer()->SetCount(0);
		}
		if (Input::GetKeyDown(eKeyCode::LBTN))
		{
			PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::Attacking);
			PlayerManager::GetPlayer()->SetCount(0);
		}
		
	}
	void PlayerScript::LeftRun()
	{
		if (Input::GetKey(eKeyCode::A))
		{
			Vector3 pos = mTransform->GetPosition();
			pos.x -= 0.5f * Time::DeltaTime();
			mTransform->SetPosition(pos);
		
			
			if (mCount == 0)
			{
				mTransform->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
				mAnimator->Play(L"MoveRight", true);
				PlayerManager::GetPlayer()->SetCount(1);
			}
		}

		if (Input::GetKeyUp(eKeyCode::A))
		{
			PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::Idle);
			PlayerManager::GetPlayer()->SetCount(0);

			//mTransform->SetRotation(Vector3(0.0f, 360.0f, 0.0f));
		}
	}
	void PlayerScript::RightRun()
	{
		if (Input::GetKey(eKeyCode::D))
		{

			Vector3 pos = mTransform->GetPosition();
			pos.x += 0.5f * Time::DeltaTime();
			mTransform->SetPosition(pos);

			if (mCount == 0)
			{
				mAnimator->Play(L"MoveRight", true);
				PlayerManager::GetPlayer()->SetCount(1);
			}

		}

		if (Input::GetKeyUp(eKeyCode::D))
		{
			PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::Idle);
			PlayerManager::GetPlayer()->SetCount(0);
		}

	}
	void PlayerScript::Jump()
	{

		if (mCount == 0)
		{
			
			mAnimator->Play(L"Jump", false);

			PlayerManager::GetPlayer()->SetIsGround(false);

			float JumpForce = 0.006f;
			mVelocity.y += JumpForce / mMass ;
			
			PlayerManager::GetPlayer()->SetCount(1);

		}

		if (Input::GetKey(eKeyCode::E))
		{
			PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::Fly);
			PlayerManager::GetPlayer()->SetCount(0);
		}

		if (Input::GetKeyDown(eKeyCode::I))
		{
			PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::Idle);
			PlayerManager::GetPlayer()->SetCount(0);
		}
	

	}
	void PlayerScript::Fall()
	{
		if (mCount == 0)
		{
			mAnimator->Play(L"JumpDown", false);
			PlayerManager::GetPlayer()->SetCount(1);
		}
		if (Input::GetKey(eKeyCode::A))
		{
			Vector3 pos = mTransform->GetPosition();
			pos.x -= 0.2f * Time::DeltaTime();
			mTransform->SetPosition(pos);
			mTransform->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::D))
		{
			Vector3 pos = mTransform->GetPosition();
			pos.x += 0.2f * Time::DeltaTime();
			mTransform->SetPosition(pos);

			Vector3 CheckRotation = mTransform->GetRotation();
			if (CheckRotation.y == 180.0f)
			{
				mTransform->SetRotation(Vector3(0.0f, 360.0f, 0.0f));
			}
		}
		
	}
	void PlayerScript::Hurt()
	{
	}
	void PlayerScript::Die()
	{
	}
	void PlayerScript::GroundRoll()
	{
		if (mCount == 0)
		{
			mTime = 0.0f;
			mAnimator->Play(L"GroundRoll", false);
			
			PlayerManager::GetPlayer()->SetCount(1);
		}
		Vector3 CheckRotation = mTransform->GetRotation();
		if (CheckRotation.y == 180.0f)
		{
			float rollSpeed = 0.35f;
			mPlayerPosition.x -= rollSpeed * (float)Time::DeltaTime();
			mTransform->SetPosition(mPlayerPosition);
		}
		else
		{
			float rollSpeed = 0.35f;
			mPlayerPosition.x += rollSpeed * (float)Time::DeltaTime();
			mTransform->SetPosition(mPlayerPosition);
		}

		if (mTime >= 0.5f)
		{
			PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::Idle);
			PlayerManager::GetPlayer()->SetCount(0);
		}
	
		
	}
	void PlayerScript::StartAttack()
	{
	}
	void PlayerScript::Attacking()
	{
		if (mCount == 0)
		{
			mTime = 0.0f;
			mAnimator->Play(L"Attacking", false);
			PlayerManager::GetPlayer()->SetCount(1);
		}
		if (mTime >= 0.5f)
		{
			PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::Idle);
			PlayerManager::GetPlayer()->SetCount(0);
		}
	}
	void PlayerScript::StartFly()
	{
	}
	void PlayerScript::Fly()
	{

		mIsFlying = true;

		Vector2 movement = Vector2::Zero;

		if (mCount == 0)
		{
			mGravity = 0.0f;
			mAnimator->Play(L"Flying", true);
			PlayerManager::GetPlayer()->SetCount(1);
		}
		


		if (Input::GetKey(eKeyCode::A))
		{
			movement.x -= 1.0f;
			mTransform->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::D))
		{
			movement.x += 1.0f;
			Vector3 CheckRotation = mTransform->GetRotation();
			if (CheckRotation.y == 180.0f)
			{
				mTransform->SetRotation(Vector3(0.0f, 360.0f, 0.0f));
			}
		}
		if (Input::GetKey(eKeyCode::S))
		{
			movement.y -= 1.0f;
			PlayerManager::GetPlayer()->SetIsFlyDown(true);
		}
		if (Input::GetKeyUp(eKeyCode::S))
		{
			PlayerManager::GetPlayer()->SetIsFlyDown(false);
		}
		if (Input::GetKey(eKeyCode::W))
		{
			movement.y += 1.0f;
		}
		if (Input::GetKeyDown(eKeyCode::LBTN))
		{
			PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::FlyAttack);
			PlayerManager::GetPlayer()->SetCount(0);
		}
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::FlyRoll);
			PlayerManager::GetPlayer()->SetCount(0);
		}
		if (Input::GetKeyDown(eKeyCode::I))
		{
			PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::Idle);
			PlayerManager::GetPlayer()->SetCount(0);
		}

		if (movement != Vector2::Zero)
		{
			movement.Normalize();
			movement *= mSpeed;
		}
		Vector3 pos = mTransform->GetPosition();
		pos += Vector3(movement.x, movement.y, 0.0f) * Time::DeltaTime();
		mTransform->SetPosition(pos);

	}
	void PlayerScript::FlyGrab()
	{
		if (mCount == 0)
		{

			mTime = 0.0f;
			mAnimator->Play(L"FlyGrab", true);
			PlayerManager::GetPlayer()->SetCount(1);
		}

		Vector2 movement = Vector2::Zero;



		if (Input::GetKey(eKeyCode::A))
		{
			movement.x -= 1.0f;
			mTransform->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::D))
		{
			movement.x += 1.0f;
			Vector3 CheckRotation = mTransform->GetRotation();
			if (CheckRotation.y == 180.0f)
			{
				mTransform->SetRotation(Vector3(0.0f, 360.0f, 0.0f));
			}
		}
		if (Input::GetKey(eKeyCode::S))
		{
			movement.y -= 1.0f;
			PlayerManager::GetPlayer()->SetIsFlyDown(true);
		}
		if (Input::GetKeyUp(eKeyCode::S))
		{
			PlayerManager::GetPlayer()->SetIsFlyDown(false);
		}
		if (Input::GetKey(eKeyCode::W))
		{
			movement.y += 1.0f;
		}

		if (movement != Vector2::Zero)
		{
			movement.Normalize();
			movement *= mSpeed;
		}
		Vector3 pos = mTransform->GetPosition();
		pos += Vector3(movement.x, movement.y, 0.0f) * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}
	void PlayerScript::FlyCarry()
	{
	}

	void PlayerScript::FlyAttack()
	{
		if (mCount == 0)
		{
			mTime = 0.0f;
			mAnimator->Play(L"Attacking", false);
			PlayerManager::GetPlayer()->SetCount(1);
		}
		if (mTime >= 0.5f)
		{
			PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::Fly);
			PlayerManager::GetPlayer()->SetCount(0);
		}
	}

	void PlayerScript::StartFlyRoll()
	{
	}

	void PlayerScript::FlyRoll()
	{
		if (mCount == 0)
		{
			mTime = 0.0f;
			mAnimator->Play(L"FlyRoll", false);
			PlayerManager::GetPlayer()->SetCount(1);
		}
		if (mTime >= 0.5f)
		{
			PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::Fly);
			PlayerManager::GetPlayer()->SetCount(0);
		}
		Vector3 CheckRotation = mTransform->GetRotation();
		if (CheckRotation.y == 180.0f)
		{
			float rollSpeed = 0.35f;
			mPlayerPosition.x -= rollSpeed * (float)Time::DeltaTime();
			mTransform->SetPosition(mPlayerPosition);
		}
		else
		{
			float rollSpeed = 0.35f;
			mPlayerPosition.x += rollSpeed * (float)Time::DeltaTime();
			mTransform->SetPosition(mPlayerPosition);
		}
	}



	void PlayerScript::JumpComplete()
	{

		mAnimator->Play(L"JumpDown", false);

	}

}