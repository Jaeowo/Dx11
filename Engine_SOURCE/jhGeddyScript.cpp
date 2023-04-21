#include "jhGeddyScript.h"
#include "jhPlayerManager.h"
#include "jhGeddy.h"
#include "jhResources.h"
#include "jhGameObject.h"
#include "jhAnimator.h"
#include "jhGeddyBullet.h"
#include "jhObject.h"

#include "jhInput.h"

namespace jh
{
	GeddyScript::GeddyScript()
		: mGeddyState(eGeddyState::Idle)
		, mCount(0)
	{
		
		Animator* mAnimator = PlayerManager::GetGeddy()->AddComponent<Animator>();

		

		std::shared_ptr<Texture> geddytexture = Resources::Load<Texture>(L"geddy", L"Geddy\\spr_mechanic_96x96.png");
		mAnimator->Create(L"IdleG", geddytexture, Vector2(0.0f, 0.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 11, 0.25f);
		mAnimator->Create(L"HaingingG", geddytexture, Vector2(0.0f, 96.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 5, 0.25f);

		/*
		mVelocity = (Vector2(0.0f, 0.0f));
		mMass = 150.0f;

		mGravity = 0.001f;
	
		Animator* mAnimator = PlayerManager::GetPlayer()->AddComponent<Animator>();
		*/
	}
	GeddyScript::~GeddyScript()
	{
	}
	void GeddyScript::Initalize()
	{
	}
	void GeddyScript::Update()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();
		mTransform = GetOwner()->GetComponent<Transform>();

		mGeddyPosition = mTransform->GetPosition();
		PlayerManager::GetGeddy()->SetPlayerState(mGeddyState);
		PlayerManager::GetGeddy()->SetPlayerPos(mGeddyPosition);

		/*

		
		mPlayerPosition = mTransform->GetPosition();
		mTime += Time::DeltaTime();
		PlayerManager::GetPlayer()->SetPlayerState(mPlayerState);
		PlayerManager::GetPlayer()->SetPlayerPos(mPlayerPosition);
		
		*/


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
		default:
			break;
		}

		if (Input::GetKeyDown(eKeyCode::G))
		{
			mGeddyState = eGeddyState::Hanging;
			mCount = 0;
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
			mAnimator->Play(L"HaingingG", true);
			mCount = 1;
		}
	}
	void GeddyScript::Hanging()
	{
		if (mCount == 0)
		{
			mAnimator->Play(L"HaingingG", true);
			mCount = 1;

		}
	}
}