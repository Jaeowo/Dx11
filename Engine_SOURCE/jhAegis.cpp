#include "jhAegis.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhObject.h"
#include "jhAnimator.h"
#include "jhPlayer.h"
#include "jhPlayerManager.h"
#include "jhTime.h"

namespace jh
{
	Aegis::Aegis()
		: mOneCount(false)
		, mTotalTime(0.0f)
		, mRotation(Vector3(0.0f, 0.0f, 0.0f))
		, mPosition(Vector3(0.0f, 0.0f, 0.0f))
		, mHp(4)
		, mMinY(-0.1f)
		, mMaxY(0.1f)
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.1f, 0.1f));

		mTransform->SetScale(Vector3(0.3f, 0.3f, 1.0f));

		SpriteRenderer* gawksr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> gawkmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> gawkmaterial = Resources::Find<Material>(L"GawkMaterial");
		gawksr->SetMaterial(gawkmaterial);
		gawksr->SetMesh(gawkmesh);

		std::shared_ptr<Texture> aegistexture = Resources::Load<Texture>(L"Aegis", L"Mini Aegis\\spr_AegisMini_43x57.png");

		mAnimator->Create(L"AegisIdle", aegistexture, Vector2(0.0f, 0.0f), Vector2(43.0f, 57.0f), Vector2::Zero, 1, 0.2f);
	

		mAnimator->Play(L"AegisIdle", true);


	}
	Aegis::~Aegis()
	{
	}
	void Aegis::Initalize()
	{
		GameObject::Initalize();
		mTargetPosition = PlayerManager::GetPlayer()->GetPlayerPos();
	}
	void Aegis::Update()
	{
		GameObject::Update();
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);
		mTargetPosition = PlayerManager::GetPlayer()->GetPlayerPos();
		mTransform->SetRotation(mRotation);

		switch (mAegisState)
		{
		case jh::eAegisState::Idle:
			Idle();
			break;
		case jh::eAegisState::WaitShoot:
			WaitShoot();
			break;
		case jh::eAegisState::Shoot:
			Shoot();
			break;
		case jh::eAegisState::Die:
			Die();
			break;
		default:
			break;
		}
	}
	void Aegis::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Aegis::Render()
	{
		GameObject::Render();
	}

	void Aegis::Idle()
	{
	}

	void Aegis::WaitShoot()
	{
		float speed = 0.1f; 
		Vector3 direction(0.0f, mTargetPosition.y - mPosition.y, 0.0f); 

		direction.Normalize();

		mPosition += direction * speed * Time::DeltaTime();

		if (mPosition.y < mMinY) {
			mPosition.y = mMinY;
		}
		else if (mPosition.y > mMaxY) {
			mPosition.y = mMaxY;
		}

		mTransform->SetPosition(mPosition);
	}

	void Aegis::Shoot()
	{
	}

	void Aegis::Die()
	{
	}

}