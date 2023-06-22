#include "jhAegisBullet.h"
#include "jhTime.h"
#include "jhResources.h"
#include "jhSpriteRenderer.h"
#include "jhAnimator.h"
#include "jhPlayerManager.h"
#include "jhPlayer.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"

namespace jh
{
	AegisBullet::AegisBullet()
		: mSpeed(0.4f)
		, mIsAttack(false)
		, mIsDirectionSet(false)
		, mDeadTime(0.0f)
	{

		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mTransform->SetPosition(Vector3(0.887f, 0.823f, 1.7f));
		mTransform->SetScale(Vector3(0.32f, 0.32f, 1.0f));
		mTransform->SetRotation(Vector3(0.0f, 180.0f, 0.0f));

		SpriteRenderer* tortoisebulletsr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> tortoisebulletmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> tortoisebulletmaterial = Resources::Find<Material>(L"Mechanicbulletmaterial");
		tortoisebulletsr->SetMaterial(tortoisebulletmaterial);
		tortoisebulletsr->SetMesh(tortoisebulletmesh);

		std::shared_ptr<Texture> aegisbullettexture = Resources::Load<Texture>
			(L"AegisBullet", L"Mini Aegis\\wardBullet_29x14_strip7.png");

		mAnimator->Create(L"AegisBullet", aegisbullettexture,
			Vector2(0.0f, 0.0f), Vector2(29.0f, 14.0f), Vector2::Zero, 7, 0.2f);

		mAnimator->Play(L"AegisBullet", true);



		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.1f, 0.1f));

		std::shared_ptr<AudioClip> audioClip = Resources::Load<AudioClip>
			(L"Shoot1", L"..\\Resources\\Audio\\shoot1.wav");

		AudioSource* audioSource = AddComponent<AudioSource>();
		audioSource->SetClip(audioClip);
		audioSource->SetLoop(false);


		audioSource->Play();
	}

	AegisBullet::~AegisBullet()
	{
	}
	void AegisBullet::Initalize()
	{
		GameObject::Initalize();

	}
	void AegisBullet::Update()
	{

		GameObject::Update();

		if (mIsDirectionSet)
		{
			mTransform->SetPosition(mTransform->GetPosition() + mDirection * mSpeed * Time::DeltaTime());
		}

		if (mDeadTime >= 3.0f)
		{
			this->Death();
		}

	}
	void AegisBullet::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void AegisBullet::Render()
	{
		GameObject::Render();
	}
	void AegisBullet::SetPosition(const Vector3& position)
	{
		mTransform->SetPosition(position);
		mBulletPos = mTransform->GetPosition();
	}
	void AegisBullet::SetDirection(const Vector3& direction)
	{
		mDirection = direction;
		mIsDirectionSet = true;
	}
}