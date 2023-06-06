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

		mTransform->SetScale(Vector3(2.3f, 2.3f, 1.0f));
		mTransform->SetPosition(mPosition);

		SpriteRenderer* numbersr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> numbermesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> numbermaterial = Resources::Find<Material>(L"NumberMaterial");
		numbersr->SetMaterial(numbermaterial);
		numbersr->SetMesh(numbermesh);

		std::shared_ptr<Texture> numbertexture = Resources::Load<Texture>(L"Number", L"UI\\Number.png");
		mAnimator->Create(L"number1", numbertexture, Vector2(0.0f, 0.0f), Vector2(8.0f, 0.0f), Vector2::Zero, 5, 0.3f);

		mAnimator->Play(L"number1", false);
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