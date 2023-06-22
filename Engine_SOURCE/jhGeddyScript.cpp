#include "jhGeddyScript.h"
#include "jhPlayerManager.h"
#include "jhGeddy.h"
#include "jhResources.h"
#include "jhGameObject.h"
#include "jhAnimator.h"
#include "jhGeddyBullet.h"
#include "jhObject.h"
#include "jhGeddyhands.h"
#include "jhPlayer.h"
#include "jhPlayerManager.h"
#include "jhTime.h"
#include "jhCollider2D.h"
#include "jhGround.h"

#include "jhInput.h"

#include "jhSpriteRenderer.h"
#include "jhBurstEffect.h"
#include "jhSmallDustEffect.h"
#include "jhBigDustEffect.h"

namespace jh
{
	GeddyScript::GeddyScript()
		: mGeddyState(eGeddyState::Idle)
		, mCount(0)
		, mbGround(false)
		, mFallingTime(0.0f)
		, mGeddyhands(nullptr)
	{
		
		

		mVelocity = (Vector2(0.0f, 0.0f));
		mMass = 150.0f;

		mGravity = 0.00005f;

		//Geddyhands * mGeddyhands = object::Instantiate<Geddyhands>(eLayerType::PlayerObject);
		//geddyhands->Death();

	

	}
	GeddyScript::~GeddyScript()
	{
	}
	void GeddyScript::Initalize()
	{
		mGeddy = dynamic_cast<Geddy*>(GetOwner());
		if (mGeddy == nullptr)
		{
			return;
		}

		Animator* mAnimator = PlayerManager::GetGeddy()->AddComponent<Animator>();
		//sprFlailLoop_strip8
		std::shared_ptr<Texture> geddyfalltexture = Resources::Load<Texture>(L"geddyfall", L"Geddy\\sprFlailLoop_strip8.png");
		std::shared_ptr<Texture> geddytexture = Resources::Load<Texture>(L"geddy", L"Geddy\\spr_mechanic_96x96.png");

		mAnimator->Create(L"IdleG", geddytexture, Vector2(0.0f, 0.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 11, 0.25f);
		mAnimator->Create(L"HaingingG", geddytexture, Vector2(0.0f, 96.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 5, 0.25f);
		mAnimator->Create(L"fallG", geddyfalltexture, Vector2(0.0f, 96.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 8, 0.25f);

		mPlayerTransform = PlayerManager::GetPlayer()->getTransform();
	}
	void GeddyScript::Update()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();
		mTransform = GetOwner()->GetComponent<Transform>();

		mGeddyState = mGeddy->GetGeddyState();
		mGeddyPosition = mTransform->GetPosition();
		//mGeddy->SetGeddyPos(mGeddyPosition);
		mCount = mGeddy->GetCount();
		//mGeddy->SetPlayerPos(mGeddyPosition);
		mTransform->SetPosition(mGeddyPosition);

		switch (mGeddyState)
		{
		case jh::enums::eGeddyState::Idle:
			Idle();
			break;
		case jh::enums::eGeddyState::Hanging:
			Hanging();
			break;
		case jh::enums::eGeddyState::Shooting:
			break;
		case jh::enums::eGeddyState::Falling:
			Falling();
			break;
		default:
			break;
		}

#pragma region FALL
		float deltaY = mGeddyPosition.y - mBeforePos.y;

		if (mbGround)
		{
			if (deltaY < 0.0f)
			{
				mFallingTime += Time::DeltaTime();

				if (mFallingTime > 0.1f)
				{
					if (mGeddyState != eGeddyState::Falling)
					{
						mGeddy->SetCount(0);
						mGeddy->SetGeddyState(eGeddyState::Falling);
					}

					mFallingTime = 0.0f;

				}
			}
			else
			{
				mFallingTime = 0.0f;
			}
		}

		mBeforePos = mGeddyPosition;

#pragma endregion

		if (mGeddy->GetIsGround() == true)
		{
			mGravity = 0.0f;
			mVelocity.y = 0.0f;
		}
		else if (mGeddy->GetIsGround() == false)
		{
			mGravity = 0.00005f;
		}


		if (mGeddyState != eGeddyState::Hanging)
		{
			mGeddyPosition.x += mVelocity.x * (float)Time::DeltaTime();
			mGeddyPosition.y += mVelocity.y + 0.5f * mGravity * (float)Time::DeltaTime() * (float)Time::DeltaTime();
			mVelocity.y -= mGravity * (float)Time::DeltaTime();
			mTransform->SetPosition(mGeddyPosition);
		}

	

	}
	void GeddyScript::Render()
	{
	}
	void GeddyScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void GeddyScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void GeddyScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void GeddyScript::Idle()
	{
		if (mCount == 0)
		{
		
			mAnimator->Play(L"IdleG", true);
			mGeddy->SetCount(1);
			mVelocity = (Vector2(0.0f, 0.0f));
			mMass = 150.0f;

			mGravity = 0.00005f;

		}
		if (Input::GetKeyDown(eKeyCode::G))
		{
			mGeddy->SetGeddyState(eGeddyState::Hanging);
			mGeddyState = eGeddyState::Hanging;
			mGeddy->SetCount(0);

			PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::FlyGrab);
			PlayerManager::GetPlayer()->SetCount(0);
		}

		if (Input::GetKeyDown(eKeyCode::Q))
		{
			Vector3 playerPos = PlayerManager::GetPlayer()->GetPlayerPos();
			mGeddy->SetGeddyPos(playerPos);
			BurstEffect* burst = object::Instantiate<BurstEffect>(eLayerType::Effect);
			burst->SetPosition(playerPos);
		}
	}
	void GeddyScript::Hanging()
	{
		if (mCount == 0)
		{
			mAnimator->Play(L"HaingingG", true);
			mGeddyhands = object::Instantiate<Geddyhands>(eLayerType::PlayerObject);

			mTransform->SetParent(mPlayerTransform);
			Vector3 PlayerScale = mPlayerTransform->GetScale();
			
			Vector3 PlayerRotation = mPlayerTransform->GetRotation();

			mTransform->SetPosition(Vector3(-0.03f, -0.1f, 0.0f));
			mTransform->SetScale(Vector3(0.95f, 0.95f, 1.0f));

			mGeddy->SetCount(1);

		}
		if (Input::GetKeyDown(eKeyCode::G))
		{

			if (mGeddyhands != nullptr)
			{
				mGeddyhands->Death();
				//bool DeadCheck = mGeddyhands->IsDead();
			}
			mGeddy->SetGeddyState(eGeddyState::Idle);

			mTransform->SetParent(nullptr);
			Vector3 PlayerPosition = mPlayerTransform->GetPosition();
			mTransform->SetPosition(Vector3(PlayerPosition.x-0.018f, PlayerPosition.y-0.05f, PlayerPosition.z));
			mTransform->SetScale(Vector3(0.33f, 0.33f, 1.0f));
			mGeddy->SetCount(0);

			PlayerManager::GetPlayer()->SetPlayerState(ePlayerState::Fly);
			PlayerManager::GetPlayer()->SetCount(0);

			
		}
		if (Input::GetKeyDown(eKeyCode::LBTN))
		{
			mGeddyhands->SetPlayerState(eGeddyhandsState::Shoot);
			mGeddyhands->SetCount(0);
			mGeddyBullet = object::Instantiate<GeddyBullet>(eLayerType::PlayerObject);
		
		}
	}
	void GeddyScript::Falling()
	{
		if (mCount == 0)
		{
			mAnimator->Play(L"fallG", false);

			mGeddy->SetCount(1);
		}
	}
}