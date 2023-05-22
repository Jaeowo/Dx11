#include "jhChest.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhAnimator.h"

namespace jh
{
	Chest::Chest()
		: mOpen(false)
	{
		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.1f, 0.1f));

		SpriteRenderer* chestsr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> chestmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> chestmaterial = Resources::Find<Material>(L"Chestmaterial");
		chestsr->SetMaterial(chestmaterial);
		chestsr->SetMesh(chestmesh);

		std::shared_ptr<Texture> gawktexture = Resources::Load<Texture>(L"Coin", L"coinSheet_18x18.png");
		mAnimator->Create(L"SpinCoin", gawktexture, Vector2(0.0f, 18.0f), Vector2(18.0f, 18.0f), Vector2::Zero, 12, 0.15f);

		mAnimator->Play(L"SpinCoin", true);
	}
	Chest::~Chest()
	{
	}
	void Chest::Initalize()
	{
		GameObject::Initalize();

	}
	void Chest::Update()
	{
		GameObject::Update();

		if (mOpen == true)
		{

		}
		else
		{

		}

	}
	void Chest::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Chest::Render()
	{
		GameObject::Render();
	}
}