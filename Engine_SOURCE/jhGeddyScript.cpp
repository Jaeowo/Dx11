#include "jhGeddyScript.h"
#include "jhPlayerManager.h"
#include "jhGeddy.h"
#include "jhResources.h"
#include "jhGameObject.h"
#include "jhAnimator.h"

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