#include "jhBurstEffect.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhAnimator.h"
#include "jhTime.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"

namespace jh
{
	BurstEffect::BurstEffect()
		:mOneCount(false)
		, mTime(0.0f)
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mTransform->SetPosition(mPosition);
		mTransform->SetScale(Vector3(0.3f, 0.3f, 1.0f));

		SpriteRenderer* horizontalsr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> horizontalmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> horizontalmaterial = Resources::Find<Material>(L"Horizontalmaterial");
		horizontalsr->SetMaterial(horizontalmaterial);
		horizontalsr->SetMesh(horizontalmesh);


		std::shared_ptr<Texture> Bursttexture = Resources::Load<Texture>
			(L"BurstEffect", L"Effect\\OwlOrbBurstStraight_66x111_strip9.png");

		mAnimator->Create(L"Burst", Bursttexture, Vector2(0.0f, 0.0f), Vector2(66.0f, 111.0f), Vector2::Zero, 9, 0.1f);


		mAnimator->Play(L"Burst", false);

		std::shared_ptr<AudioClip> audioClip = Resources::Load<AudioClip>
			(L"Flash", L"..\\Resources\\Audio\\flash.wav");

		AudioSource* audioSource = AddComponent<AudioSource>();
		audioSource->SetClip(audioClip);
		audioSource->SetLoop(false);


		audioSource->Play();

	}
	BurstEffect::~BurstEffect()
	{
	}
	void BurstEffect::Initalize()
	{
		GameObject::Initalize();
	}
	void BurstEffect::Update()
	{
		GameObject::Update();
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);

		mTime += Time::DeltaTime();

		if (mTime >= 0.6f)
		{
			Death();
		}

	}
	void BurstEffect::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void BurstEffect::Render()
	{
		GameObject::Render();
	}


}