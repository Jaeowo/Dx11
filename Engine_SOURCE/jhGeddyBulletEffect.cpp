#include "jhGeddyBulletEffect.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhAnimator.h"
#include "jhTime.h"

namespace jh
{
	GeddyBulletEffect::GeddyBulletEffect()
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


		std::shared_ptr<Texture> GBEffecttexture = Resources::Load<Texture>
			(L"GeddyBulletEffect", L"Geddy\\sprMechanicBulletEffect_41x40_strip18.png");

		mAnimator->Create(L"GBEffect", GBEffecttexture, Vector2(0.0f, 0.0f), Vector2(41.0f, 40.0f), Vector2::Zero, 18, 0.1f);


		mAnimator->Play(L"GBEffect", false);


	}
	GeddyBulletEffect::~GeddyBulletEffect()
	{
	}
	void GeddyBulletEffect::Initalize()
	{
		GameObject::Initalize();
	}
	void GeddyBulletEffect::Update()
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
	void GeddyBulletEffect::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void GeddyBulletEffect::Render()
	{
		GameObject::Render();
	}


}