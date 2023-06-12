#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhAnimator.h"
#include "jhPlayerManager.h"
#include "jhPlayer.h"
#include "jhResources.h"
#include "jhGeddy.h"
#include "jhPlayerAttackCol.h"
#include "jhObject.h"

namespace jh
{
	PlayerScript::PlayerScript()
		:Script()
		, mPlayerState(ePlayerState::Idle)
		, mbGround(false)
		, mbCarrying(false)
		, mCount(0)
		, mTime(0.0f)
		, mSpeed(0.5f)
		, mFallingTime(0.0f)
		, mIsFlying(false)
	{

		mVelocity = (Vector2(0.0f, 0.0f));
		mMass = 250.0f;

		mGravity = 0.00005f;
	
	

		
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initalize()
	{
		mPlayer = dynamic_cast<Player*>(GetOwner());
		if (mPlayer == nullptr)
		{
			return;
		}
		Animator* mAnimator = mPlayer->AddComponent<Animator>();


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
	void PlayerScript::Update()
	{

		mTransform = GetOwner()->GetComponent<Transform>();
		mAnimator = GetOwner()->GetComponent<Animator>();

		mRotation = mPlayer->GetPlayerRotation();
		mPlayer->SetPreviousPos(mPlayerPosition);

		mPlayerPosition = mTransform->GetPosition();
		mTime += Time::DeltaTime();
		mPlayerState = mPlayer->GetPlayerState();
		mPlayer->SetPlayerPos(mPlayerPosition);

		mCount = mPlayer->GetCount();


		mHp = mPlayer->GetHp();
		mCoin = mPlayer->GetCoin();

		if (mPlayer->GetEventTrigger() == true)
		{
			mPrevState = mPlayerState;
			mPlayerState = ePlayerState::Event;
		}

		if (mPlayer->GetHurt() == true)
		{
			mPrevState = mPlayerState;

			if (mIsFlying == true)
			{
				mPlayerState = ePlayerState::FlyHurt;
			}
			else
			{
				mPlayerState = ePlayerState::Hurt;
			}
		}

		if (mPlayer->GetVelocityZero() == true)
		{
			mVelocity.x = 0.0f;
			mVelocity.y = 0.0f;
		}

#pragma region FALL
		float deltaY = mPlayerPosition.y - mPrevPosition.y;

		if (!mbGround)
			{
			if (deltaY < 0.0f)
			{
				mFallingTime += Time::DeltaTime();

				if (mFallingTime > 0.1f)
				{	
					if (mPlayerState != ePlayerState::Fall && mIsFlying == false)
					{
						mPlayer->SetCount(0);
						mPlayer->SetPlayerState(ePlayerState::Fall);
					}

					mFallingTime = 0.0f;
	
				}
			}
			else
			{
				mFallingTime = 0.0f;
			}
		}
	
		mPrevPosition = mPlayerPosition;
	
#pragma endregion

		mPlayer->SetIsFly(mIsFlying);

		if (mPlayer->GetIsGround() == true && mPlayerState != ePlayerState::Jump)
		{
			mGravity = 0.0f;
			mVelocity.y = 0.0f;
		}
		else if (mPlayer->GetIsGround() == false && mIsFlying == false)
		{
			mGravity = 0.00015f;
		}

		mPlayerPosition.x += mVelocity.x * (float)Time::DeltaTime();

		if (mIsFlying == false)
		{
			mPlayerPosition.y += mVelocity.y + 0.5f * mGravity * (float)Time::DeltaTime() * (float)Time::DeltaTime();
			mVelocity.y -= mGravity * (float)Time::DeltaTime();
		}

		mTransform->SetPosition(mPlayerPosition);

	
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
			EnterDoor();
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
			FlyHurt();
			break;
		case jh::enums::ePlayerState::FlyAttack:
			FlyAttack();
			break;
		case jh::enums::ePlayerState::Eat:
			break;
		case jh::enums::ePlayerState::Hurt:
			Hurt();
			break;
		case jh::enums::ePlayerState::Die:
			break;
		case jh::enums::ePlayerState::Event:
			EventOn();
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
	
	}
	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void PlayerScript::Idle()
	{
		if (mCount == 0)
		{
			mVelocity.x = 0.0f;
			mVelocity.y = 0.0f;

			mIsFlying = false;
			mAnimator->Play(L"Idle", true);
			mPlayer->SetCount(1);
			mPlayer->SetIsFlyDown(false);
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			//Vector3 CheckRotation = mTransform->GetRotation();
			if (mRotation.y == 180.0f)
			{
				//mTransform->SetRotation(Vector3(0.0f, 360.0f, 0.0f));
				mPlayer->SetPlayerRotation(Vector3(0.0f, 360.0f, 0.0f));
			}
			mPlayer->SetPlayerState(ePlayerState::RightRun);
			mPlayer->SetCount(0);
			
			

		}
		if (Input::GetKeyDown(eKeyCode::A))
		{
			mPlayer->SetPlayerState(ePlayerState::LeftRun);
			mPlayer->SetCount(0);
		}
		if (Input::GetKeyDown(eKeyCode::W))
		{
			mPlayer->SetPlayerState(ePlayerState::Jump);
			mPlayer->SetCount(0);
		}
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			mPlayer->SetPlayerState(ePlayerState::GroundRoll);
			mPlayer->SetCount(0);
		}
		if (Input::GetKeyDown(eKeyCode::LBTN))
		{
			mPlayer->SetPlayerState(ePlayerState::Attacking);
			mPlayer->SetCount(0);
		}
		
	}
	void PlayerScript::LeftRun()
	{
		const float SlopeAngle = 0.5f; 

		if (Input::GetKey(eKeyCode::A))
		{
			Vector3 pos = mTransform->GetPosition();
			pos.x -= 0.35f * Time::DeltaTime();

			if (mPlayer->GetIsLeftSlope() == true)
			{
				pos.y += SlopeAngle * Time::DeltaTime(); 
				mGravity = 0.0f;  
			}
			else if (mPlayer->GetIsLeftSlope() == false)
			{
				mGravity = 0.00005f;
			}
			mTransform->SetPosition(pos);

			if (mCount == 0)
			{
				mPlayer->SetPlayerRotation(Vector3(0.0f, 180.0f, 0.0f));
				mAnimator->Play(L"MoveRight", true);
				mPlayer->SetCount(1);
			}
		}

		if (Input::GetKeyUp(eKeyCode::A))
		{
			mPlayer->SetPlayerState(ePlayerState::Idle);
			mPlayer->SetCount(0);
		}

		mVelocity.x = -0.05f;

		if (Input::GetKeyDown(eKeyCode::W))
		{
			mPlayer->SetPlayerState(ePlayerState::Jump);
			mPlayer->SetCount(0);
		}
	}
	void PlayerScript::RightRun()
	{


		if (Input::GetKey(eKeyCode::D))
		{

			Vector3 pos = mTransform->GetPosition();
			pos.x += 0.35f * Time::DeltaTime();
			

			const float SlopeAngle = 0.5f;

			if (mPlayer->GetIsLeftSlope() == true)
			{
				pos.y -= SlopeAngle * Time::DeltaTime();
				mGravity = 0.0f;
			}
			else if (mPlayer->GetIsLeftSlope() == false)
			{
				mGravity = 0.00005f;
			}

			if (mCount == 0)
			{
				mAnimator->Play(L"MoveRight", true);
				mPlayer->SetCount(1);
			}
			mTransform->SetPosition(pos);
		}

		if (Input::GetKeyUp(eKeyCode::D))
		{
			mPlayer->SetPlayerState(ePlayerState::Idle);
			mPlayer->SetCount(0);
		}
		mVelocity.x = 0.05f;

		if (Input::GetKeyDown(eKeyCode::W))
		{
			mPlayer->SetPlayerState(ePlayerState::Jump);
			mPlayer->SetCount(0);
		}
	}
	void PlayerScript::Jump()
	{

		if (mCount == 0)
		{
			mAnimator->Play(L"Jump", false);
			mPlayer->SetIsGround(false);

			float JumpForce = 0.02f;
			mVelocity.y += JumpForce / mMass;

			mPlayer->SetCount(1);

		
			mTime = 0.0f;
		}

		if (Input::GetKey(eKeyCode::W) && mTime <= 0.2f)
		{
			float additionalJumpForce = 0.00008f;
			mVelocity.y += additionalJumpForce / mMass;
		}

		if (Input::GetKey(eKeyCode::E))
		{
			mPlayer->SetPlayerState(ePlayerState::Fly);
			mPlayer->SetCount(0);
		}

	

	}
	void PlayerScript::Fall()
	{
		if (mCount == 0)
		{
			mVelocity.x = 0.0f;
			mVelocity.y = 0.0f;
			mAnimator->Play(L"JumpDown", false);
			mPlayer->SetCount(1);
		}
		if (Input::GetKey(eKeyCode::A))
		{
			Vector3 pos = mTransform->GetPosition();
			pos.x -= 0.2f * Time::DeltaTime();
			mTransform->SetPosition(pos);
			mPlayer->SetPlayerRotation(Vector3(0.0f, 180.0f, 0.0f));
			//mTransform->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::D))
		{
			Vector3 pos = mTransform->GetPosition();
			pos.x += 0.2f * Time::DeltaTime();
			mTransform->SetPosition(pos);

			//Vector3 CheckRotation = mTransform->GetRotation();
			if (mRotation.y == 180.0f)
			{
				mPlayer->SetPlayerRotation(Vector3(0.0f, 360.0f, 0.0f));
				//mTransform->SetRotation(Vector3(0.0f, 360.0f, 0.0f));
			}
		}
		
	}
	void PlayerScript::Hurt()
	{
		if (mCount == 0)
		{
			mTime = 0.0f;
			mAnimator->Play(L"hurt", false);
			mVelocity.x = 0;
			mCount = 1;

			mPlayer->SetHurt(false);
		}
		if (mTime >= 0.5f)
		{
			mPlayerState = mPrevState;
			mCount = 0;
		}

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
			
			mPlayer->SetCount(1);
		}
		//Vector3 CheckRotation = mTransform->GetRotation();
		if (mRotation.y == 180.0f)
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
			mPlayer->SetPlayerState(ePlayerState::Idle);
			mPlayer->SetCount(0);
		}
	
		
	}
	void PlayerScript::EnterDoor()
	{
		if (mCount == 0)
		{
			mTime = 0.0f;
			mAnimator->Play(L"EnterDoor", false);
			mPlayer->SetCount(1);
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

			if (mAttackCol == nullptr)
			{
				mAttackCol = object::Instantiate<PlayerAttackCol>(eLayerType::Player);
			}

			mPlayer->SetCount(1);
		}
		if (mTime >= 0.5f)
		{
			mPlayer->SetPlayerState(ePlayerState::Idle);
			mPlayer->SetCount(0);

			if (mAttackCol != nullptr)
			{
				mAttackCol->Death();
			}
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
			mPlayer->SetCount(1);
		}
		


		if (Input::GetKey(eKeyCode::A))
		{
			movement.x -= 1.0f;
			mPlayer->SetPlayerRotation(Vector3(0.0f, 180.0f, 0.0f));
			//mTransform->SetRotation(Vector3(0.0f, 180.0f, 0.0f));

		}
		if (Input::GetKey(eKeyCode::D))
		{
			movement.x += 1.0f;
			//Vector3 CheckRotation = mTransform->GetRotation();
			if (mRotation.y == 180.0f)
			{
				//mTransform->SetRotation(Vector3(0.0f, 360.0f, 0.0f));
				mPlayer->SetPlayerRotation(Vector3(0.0f, 360.0f, 0.0f));
			}
		}
		if (Input::GetKey(eKeyCode::S))
		{
			movement.y -= 1.0f;
			mPlayer->SetIsFlyDown(true);
		}
		if (Input::GetKeyUp(eKeyCode::S))
		{
			mPlayer->SetIsFlyDown(false);
		}
		if (Input::GetKey(eKeyCode::W))
		{
			movement.y += 1.0f;
		}
		if (Input::GetKeyDown(eKeyCode::LBTN))
		{
			mPlayer->SetPlayerState(ePlayerState::FlyAttack);
			mPlayer->SetCount(0);
		}
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			mPlayer->SetPlayerState(ePlayerState::FlyRoll);
			mPlayer->SetCount(0);
		}
		if (Input::GetKeyDown(eKeyCode::I))
		{
			mPlayer->SetPlayerState(ePlayerState::Idle);
			mPlayer->SetCount(0);
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
			mPlayer->SetCount(1);
		}

		Vector2 movement = Vector2::Zero;



		if (Input::GetKey(eKeyCode::A))
		{
			movement.x -= 1.0f;
			//mTransform->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
			mPlayer->SetPlayerRotation(Vector3(0.0f, 180.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::D))
		{
			movement.x += 1.0f;
			//Vector3 CheckRotation = mTransform->GetRotation();
			if (mRotation.y == 180.0f)
			{
				//mTransform->SetRotation(Vector3(0.0f, 360.0f, 0.0f));
				mPlayer->SetPlayerRotation(Vector3(0.0f, 360.0f, 0.0f));
			}
		}
		if (Input::GetKey(eKeyCode::S))
		{
			movement.y -= 1.0f;
			mPlayer->SetIsFlyDown(true);
		}
		if (Input::GetKeyUp(eKeyCode::S))
		{
			mPlayer->SetIsFlyDown(false);
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

			if (mAttackCol == nullptr)
			{
				mAttackCol = object::Instantiate<PlayerAttackCol>(eLayerType::Player);
			}

			mPlayer->SetCount(1);
		}
		if (mTime >= 0.5f)
		{
			mPlayer->SetPlayerState(ePlayerState::Fly);
			mPlayer->SetCount(0);

			if (mAttackCol != nullptr)
			{
				mAttackCol->Death();
			}
		}
	}

	void PlayerScript::FlyHurt()
	{
		if (mCount == 0)
		{
			mTime = 0.0f;
			mAnimator->Play(L"flyinghurt", false);
			mCount = 1;
		}
		if (mTime >= 0.2f)
		{
			mPlayerState = mPrevState;
			mCount = 0;
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
			mPlayer->SetCount(1);
		}
		if (mTime >= 0.5f)
		{
			mPlayer->SetPlayerState(ePlayerState::Fly);
			mPlayer->SetCount(0);
		}

		if (mRotation.y == 180.0f)
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

	void PlayerScript::EventOn()
	{
		if (mPlayer->GetEventTrigger() == false)
		{
			mPlayerState = mPrevState;
		}
	}

	void PlayerScript::JumpComplete()
	{

		mAnimator->Play(L"JumpDown", false);

	}

}