#include "jhCoin.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhAnimator.h"
#include "jhTime.h"
#include "jhCoinScript.h"

namespace jh
{
	Coin::Coin()
		:mVelocity(0.0f, 0.0f, 0.0f)
		,mSpeed(0.3f)
		,mGravity(0.5f)
		,mPosition(Vector3(0.0f, 0.0f, 0.0f))
		,mbGround(false)
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mTransform->SetScale(Vector3(0.3f, 0.3f, 1.0f));
		mTransform->SetPosition(mPosition);

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
		AddComponent<CoinScript>();
		GameObject::Initalize();

	}
	void Coin::Update()
	{
		GameObject::Update();




		if (mbGround == true)
		{
			mGravity = 0.0f;
			mVelocity.y = 0.0f;
		}
		else
		{

			mVelocity.y -= mGravity * Time::DeltaTime();

			mPosition += mVelocity * Time::DeltaTime();

			mTransform = GetComponent<Transform>();
			mTransform->SetPosition(mPosition);
		}

	}
	void Coin::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Coin::Render()
	{
		GameObject::Render();
	}
	void Coin::Move(const Vector3& direction)
	{
		mVelocity = direction * mSpeed;
	}
}