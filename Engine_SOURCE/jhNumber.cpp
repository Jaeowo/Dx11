#include "jhNumber.h"
#include "jhTransform.h"
#include "jhAnimator.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"

namespace jh
{
	Number::Number()
		: mPosition(Vector3(0.0f, 0.0f, 0.0f))
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mTransform->SetScale(Vector3(3.5f, 3.5f, 1.0f));
		mTransform->SetPosition(mPosition);

		SpriteRenderer* masksr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> maskmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> maskmaterial = Resources::Find<Material>(L"Horizontalmaterial");
		masksr->SetMaterial(maskmaterial);
		masksr->SetMesh(maskmesh);

		std::shared_ptr<Texture> numbertexture = Resources::Load<Texture>(L"Number", L"UI\\Number.png");
		mAnimator->Create(L"number1", numbertexture, Vector2(0.0f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"number2", numbertexture, Vector2(8.3f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"number3", numbertexture, Vector2(16.6f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"number4", numbertexture, Vector2(24.9f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"number5", numbertexture, Vector2(33.2f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"number6", numbertexture, Vector2(41.5f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"number7", numbertexture, Vector2(49.8f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"number8", numbertexture, Vector2(58.1f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"number9", numbertexture, Vector2(66.4f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"number0", numbertexture, Vector2(74.7f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);

		mAnimator->Play(L"number5", false);
	}
	Number::~Number()
	{
	}
	void Number::Initalize()
	{
		GameObject::Initalize();
	
	}
	void Number::Update()
	{
		GameObject::Update();

		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);

	}
	void Number::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Number::Render()
	{
		GameObject::Render();
	}

}