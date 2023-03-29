#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhAnimator.h"
#include "jhPlayerManager.h"
#include "jhPlayer.h"
#include "jhResources.h"

namespace jh
{
	PlayerScript::PlayerScript()
		:Script()
		, mPlayerState(ePlayerState::Idle)
		, mbGround(false)
		, mbCarrying(false)
		, mGravity(0.2f)
		, mAniCount(0)
	{
		Animator* mAnimator = PlayerManager::GetPlayer()->AddComponent<Animator>();
		std::shared_ptr<Texture> herotexture = Resources::Load<Texture>(L"hero", L"Otus\\hero.png");
		std::shared_ptr<Texture> hero2texture = Resources::Load<Texture>(L"hero2", L"Otus\\hero2.png");
		std::shared_ptr<Texture> flyUpStartCarrytexture = Resources::Load<Texture>(L"FlyUpStartCarry", L"Otus\\flyUpStartCarry_strip8.png");
		std::shared_ptr<Texture> FlyGrabtexture = Resources::Load<Texture>(L"FlyGrab", L"Otus\\sprFlyGrab_strip11.png");
		std::shared_ptr<Texture> SpreadWingstexture = Resources::Load<Texture>(L"SpreadWings", L"Otus\\sprOtusSpreadWings_112x96_strip9.png");
		std::shared_ptr<Texture> EnterDoortexture = Resources::Load<Texture>(L"EnterDoor", L"Otus\\sprOtusEnterDoor_112x96_strip13.png");
		std::shared_ptr<Texture> Dietexture = Resources::Load<Texture>(L"Die", L"Otus\\sprOtusDie_112x96_strip12.png");
		std::shared_ptr<Texture> Eattexture = Resources::Load<Texture>(L"Eat", L"Otus\\eat_strip14.png");

		mAnimator->Create(L"Idle", herotexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 13, 0.25f);
		mAnimator->Create(L"MoveRight", herotexture, Vector2(0.0f, 96.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 12, 0.2f);
		mAnimator->Create(L"Flying", herotexture, Vector2(0.0f, 192.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 11, 0.2f);
		mAnimator->Create(L"Jump", herotexture, Vector2(0.0f, 384.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 3, 0.2f);
		mAnimator->Create(L"JumpDown", herotexture, Vector2(0.0f, 480.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 5, 0.2f);
		mAnimator->Create(L"hurt", hero2texture, Vector2(0.0f, 288.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"flyinghurt", hero2texture, Vector2(0.0f, 384.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Create(L"StartAttack", hero2texture, Vector2(0.0f, 1056.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 6, 0.12f);
		mAnimator->Create(L"Attacking", hero2texture, Vector2(0.0f, 1152.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 9, 0.12f);
		mAnimator->Create(L"FlyUpStartCarry", flyUpStartCarrytexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 8, 0.12f);
		mAnimator->Create(L"FlyGrab", FlyGrabtexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 11, 0.12f);
		mAnimator->Create(L"SpreadWings", SpreadWingstexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 9, 0.15f);
		mAnimator->Create(L"EnterDoor", EnterDoortexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 13, 0.15f);
		mAnimator->Create(L"Die", Dietexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 12, 0.15f);
		mAnimator->Create(L"Eat", Eattexture, Vector2(0.0f, 0.0f), Vector2(112.0f, 96.0f), Vector2::Zero, 14, 0.15f);

		
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

		//mPlayerState = PlayerManager::GetPlayer()->SetPlayerState(mPlayerState);

		switch (mPlayerState)
		{
		case jh::enums::ePlayerState::Idle:
			Idle();
			break;
		case jh::enums::ePlayerState::LeftRun:
			break;
		case jh::enums::ePlayerState::RightRun:
			break;
		case jh::enums::ePlayerState::Jump:
			break;
		case jh::enums::ePlayerState::EnterDoor:
			break;
		case jh::enums::ePlayerState::StartAttack:
			break;
		case jh::enums::ePlayerState::Attacking:
			break;
		case jh::enums::ePlayerState::StartFly:
			break;
		case jh::enums::ePlayerState::Fly:
			break;
		case jh::enums::ePlayerState::FlyGrab:
			break;
		case jh::enums::ePlayerState::FlyCarry:
			break;
		case jh::enums::ePlayerState::FlyHurt:
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

		//if (mbGround == true && mPlayerState != ePlayerState::Fly)
		//{
		//	Vector3 pos = tr->GetPosition();
		//	pos.y -= mGravity * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}

		//if (mPlayerState == ePlayerState::Idle)
		//{

		//	if (Input::GetKey(eKeyCode::RIGHT))
		//	{
		//		Vector3 pos = tr->GetPosition();
		//		pos.x += 0.5f * Time::DeltaTime();
		//		tr->SetPosition(pos);
		//		mAnimator->Play(L"MoveRight", true);
		//	}
		//	if (Input::GetKey(eKeyCode::LEFT))
		//	{
		//		Vector3 pos = tr->GetPosition();
		//		pos.x -= 0.5f * Time::DeltaTime();
		//		tr->SetPosition(pos);
		//	}

		//	if (Input::GetKeyDown(eKeyCode::UP))
		//	{
		//		
		//		mPlayerState = ePlayerState::Jump;
		//	}
		//}

		//if (mPlayerState == ePlayerState::Jump)
		//{
		//	if (Input::GetKey(eKeyCode::UP))
		//	{
		//	/*	float MaxHeight = 0.3f;
		//		float JumpPower = 1.0f;
		//		Vector3 pos = tr->GetPosition();
		//		pos.y += JumpPower * 0.3f * Time::DeltaTime();
		//		if (pos.y >= MaxHeight)
		//		{
		//			pos.y -= mGravity * Time::DeltaTime();
		//			JumpPower = 0.0f;
		//		}
		//		tr->SetPosition(pos);*/

		//		Vector3 pos = tr->GetPosition();
		//		pos.y +=  0.3f * Time::DeltaTime();
		//		tr->SetPosition(pos);
		//	}


		//	if (Input::GetKeyUp(eKeyCode::UP))
		//	{
		//		mPlayerState = ePlayerState::Fly;
		//	}
		//}

		//if (mPlayerState == ePlayerState::Fly)
		//{
		//	
		//	if (Input::GetKey(eKeyCode::LEFT))
		//	{
		//		Vector3 pos = tr->GetPosition();
		//		pos.x -= 0.5f * Time::DeltaTime();
		//		tr->SetPosition(pos);
		//	}
		//	if (Input::GetKey(eKeyCode::DOWN))
		//	{
		//		Vector3 pos = tr->GetPosition();
		//		pos.y -= 0.5f * Time::DeltaTime();
		//		tr->SetPosition(pos);
		//	}
		//	if (Input::GetKey(eKeyCode::UP))
		//	{
		//		Vector3 pos = tr->GetPosition();
		//		pos.y += 0.5f * Time::DeltaTime();
		//		tr->SetPosition(pos);
		//	}
		//	
		//}
		
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
		if (mAniCount == 0)
		{
			mAnimator->Play(L"Idle", true);
			mAniCount = 1;
		}

		if (Input::GetKey(eKeyCode::RIGHT))
		{
			Vector3 pos = mTransform->GetPosition();
			pos.x += 0.5f * Time::DeltaTime();
			mTransform->SetPosition(pos);
		}

		
	}
	void PlayerScript::Run()
	{
	}
	void PlayerScript::Jump()
	{
	}
	void PlayerScript::Hurt()
	{
	}
	void PlayerScript::Die()
	{
	}
	void PlayerScript::StartAttack()
	{
	}
	void PlayerScript::Attacking()
	{
	}
	void PlayerScript::StartFly()
	{
	}
	void PlayerScript::Fly()
	{
	}
	void PlayerScript::FlyGrab()
	{
	}
	void PlayerScript::FlyCarry()
	{
	}
}