#include "jhTortoiseMask.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhAnimator.h"

namespace jh
{
	TortoiseMask::TortoiseMask()
		: mPosition(Vector3(0.0f, 0.0f, 0.0f))
		, mOneCount(false)
		, mTotalTime(0.0f)
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mTransform->SetScale(Vector3(0.3f, 0.3f, 1.0f));
		mTransform->SetPosition(mPosition);
		SpriteRenderer* masksr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> maskmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> maskmaterial = Resources::Find<Material>(L"Horizontalmaterial");
		masksr->SetMaterial(maskmaterial);
		masksr->SetMesh(maskmesh);

		std::shared_ptr<Texture> tortoisemasktexture = Resources::Load<Texture>
			(L"ThrowMask", L"Masked Tortoise\\Mask\\sprLand_strip9.png");

		mAnimator->Create(L"ThrowMask", tortoisemasktexture,
			Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 9, 0.23f);

		mAnimator->Play(L"ThrowMask", true);

		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.1f, 0.1f));

	}
	TortoiseMask::~TortoiseMask()
	{
	}
	void TortoiseMask::Initalize()
	{
		//AddComponent<RingScript>();
		GameObject::Initalize();
	}
	void TortoiseMask::Update()
	{
		GameObject::Update();

		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);

		//포물선 모양으로 날아가도록!

	}
	void TortoiseMask::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void TortoiseMask::Render()
	{
		GameObject::Render();
	}
}