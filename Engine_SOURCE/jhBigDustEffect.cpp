#include "jhBigDustEffect.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhAnimator.h"
#include "jhTime.h"
#include "jhAudioClip.h"
#include "jhAudioSource.h"

namespace jh
{
	BigDustEffect::BigDustEffect()
		:mOneCount(false)
		, mTime(0.0f)
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mTransform->SetPosition(mPosition);
		mTransform->SetScale(Vector3(0.5f, 0.5f, 1.0f));

		SpriteRenderer* horizontalsr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> horizontalmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> horizontalmaterial = Resources::Find<Material>(L"Horizontalmaterial");
		horizontalsr->SetMaterial(horizontalmaterial);
		horizontalsr->SetMesh(horizontalmesh);


		std::shared_ptr<Texture> bigdusttexture = Resources::Load<Texture>
			(L"BigDust", L"Effect\\smallGrey_61x54_strip18.png");

		mAnimator->Create(L"BigDust", bigdusttexture, Vector2(0.0f, 0.0f), Vector2(61.0f, 54.0f), Vector2::Zero, 18, 0.1f);


		mAnimator->Play(L"BigDust", false);

		std::shared_ptr<AudioClip> audioClip = Resources::Load<AudioClip>
			(L"Crush", L"..\\Resources\\Audio\\crush.wav");

		AudioSource* audioSource = AddComponent<AudioSource>();
		audioSource->SetClip(audioClip);
		audioSource->SetLoop(false);


		audioSource->Play();


	}
	BigDustEffect::~BigDustEffect()
	{
	}
	void BigDustEffect::Initalize()
	{
		GameObject::Initalize();
	}
	void BigDustEffect::Update()
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
	void BigDustEffect::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void BigDustEffect::Render()
	{
		GameObject::Render();
	}


}