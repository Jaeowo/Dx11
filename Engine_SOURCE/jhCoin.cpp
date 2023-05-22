#include "jhCoin.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhAnimator.h"

namespace jh
{
	Coin::Coin()
	{
		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.1f, 0.1f));

		SpriteRenderer* coinsr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> coinmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> coinmaterial = Resources::Find<Material>(L"Coinmaterial");
		coinsr->SetMaterial(coinmaterial);
		coinsr->SetMesh(coinmesh);

		std::shared_ptr<Texture> gawktexture = Resources::Load<Texture>(L"Coin", L"coinSheet_18x18.png");
		mAnimator->Create(L"SpinCoin", gawktexture, Vector2(0.0f, 18.0f), Vector2(18.0f, 18.0f), Vector2::Zero, 12, 0.15f);


		mAnimator->Play(L"SpinCoin", true);
	}
	Coin::~Coin()
	{
	}
	void Coin::Initalize()
	{
		GameObject::Initalize();

	}
	void Coin::Update()
	{
		GameObject::Update();

	}
	void Coin::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Coin::Render()
	{
		GameObject::Render();
	}
}