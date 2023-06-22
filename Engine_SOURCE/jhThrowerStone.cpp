#include "jhThrowerStone.h"
#include "jhTime.h"
#include "jhResources.h"
#include "jhSpriteRenderer.h"
#include "jhAnimator.h"
#include "jhTortoise.h"
#include "jhPlayerManager.h"
#include "jhPlayer.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"
#include "jhThrowerStoneScript.h"

namespace jh
{
	ThrowerStone::ThrowerStone()
		: mSpeed(0.5f)
		, mIsAttack(false)
		, mIsDirectionSet(false)
		, mDeadTime(0.0f)
	{

		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mTransform->SetPosition(Vector3(0.887f, 0.823f, 1.7f));
		mTransform->SetScale(Vector3(0.32f, 0.32f, 1.0f));

		SpriteRenderer* tortoisebulletsr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> tortoisebulletmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> tortoisebulletmaterial = Resources::Find<Material>(L"Mechanicbulletmaterial");
		tortoisebulletsr->SetMaterial(tortoisebulletmaterial);
		tortoisebulletsr->SetMesh(tortoisebulletmesh);

		std::shared_ptr<Texture> throwerstonetexture = Resources::Load<Texture>
			(L"ThrowerStone", L"Thrower\\webBullet_17x14.png");

		mAnimator->Create(L"ThrowStone", throwerstonetexture,
			Vector2(0.0f, 0.0f), Vector2(17.0f, 14.0f), Vector2::Zero, 1, 0.3f);
	

		mAnimator->Play(L"ThrowStone", false);

	

		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.1f, 0.1f));

	}

	ThrowerStone::~ThrowerStone()
	{
	}
	void ThrowerStone::Initalize()
	{
		GameObject::Initalize();
		AddComponent<ThrowerStoneScript>();

	}
	void ThrowerStone::Update()
	{

		GameObject::Update();

		if (!mIsDirectionSet)
		{
			mPlayerPos = PlayerManager::GetPlayer()->GetPlayerPos();
			mPlayerPos.y -= 0.06f;

			Vector2 playerPos2D(mPlayerPos.x, mPlayerPos.y);
			Vector2 bulletPos2D(mBulletPos.x, mBulletPos.y);

			mDirection = playerPos2D - bulletPos2D;
			mDirection.Normalize();

			float angle = std::atan2(mDirection.y, mDirection.x) * 180.0f / XM_PI;

			mTransform->SetRotation(Vector3(0.0f, 0.0f, angle));

			mIsDirectionSet = true;
		}

		if (mIsDirectionSet)
		{
			Vector2 velocity = mDirection * mSpeed;
			mTransform->SetPosition(mTransform->GetPosition() + Vector3(velocity.x, velocity.y, 0.0f) * Time::DeltaTime());
		}

		mDeadTime += Time::DeltaTime();

		if (mDeadTime >= 3.0f)
		{
			this->Death();
		}

	}
	void ThrowerStone::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void ThrowerStone::Render()
	{
		GameObject::Render();
	}
	void ThrowerStone::SetPosition(const Vector3& position)
	{
		mTransform->SetPosition(position);
		mBulletPos = mTransform->GetPosition();
	}
}