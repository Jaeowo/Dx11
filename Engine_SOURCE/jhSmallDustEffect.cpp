#include "jhSmallDustEffect.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhAnimator.h"
#include "jhTime.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"

namespace jh
{
	SmallDustEffect::SmallDustEffect()
		:mOneCount(false)
		, mTime(0.0f)
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mTransform->SetPosition(mPosition);
		mTransform->SetScale(Vector3(0.4f, 0.4f, 1.0f));

		SpriteRenderer* horizontalsr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> horizontalmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> horizontalmaterial = Resources::Find<Material>(L"Horizontalmaterial");
		horizontalsr->SetMaterial(horizontalmaterial);
		horizontalsr->SetMesh(horizontalmesh);


		std::shared_ptr<Texture> smalldusttexture = Resources::Load<Texture>
			(L"SmallDust", L"Effect\\directDust2_40x26_strip6.png");

		mAnimator->Create(L"SmallDust", smalldusttexture, Vector2(0.0f, 0.0f), Vector2(40.0f, 26.0f), Vector2::Zero, 6, 0.1f);


		mAnimator->Play(L"SmallDust", false);

		std::shared_ptr<AudioClip> audioClip = Resources::Load<AudioClip>
			(L"Shoot2", L"..\\Resources\\Audio\\break.wav");

		AudioSource* audioSource = AddComponent<AudioSource>();
		audioSource->SetClip(audioClip);
		audioSource->SetLoop(false);


		audioSource->Play();

	}
	SmallDustEffect::~SmallDustEffect()
	{
	}
	void SmallDustEffect::Initalize()
	{
		GameObject::Initalize();
	}
	void SmallDustEffect::Update()
	{
		GameObject::Update();
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);

		mTime += Time::DeltaTime();

		if (mTime >= 0.4f)
		{
			Death();
		}

	}
	void SmallDustEffect::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void SmallDustEffect::Render()
	{
		GameObject::Render();
	}


}