#include "jhNumberTens.h"
#include "jhTransform.h"
#include "jhAnimator.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhPlayerManager.h"
#include "jhPlayer.h"

namespace jh
{
	NumberTens::NumberTens()
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

		std::shared_ptr<Texture> numbertexture2 = Resources::Load<Texture>(L"Number2", L"UI\\Number.png");
		mAnimator->Create(L"number10", numbertexture2, Vector2(0.0f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"number20", numbertexture2, Vector2(8.3f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"number30", numbertexture2, Vector2(16.6f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"number40", numbertexture2, Vector2(24.9f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"number50", numbertexture2, Vector2(33.2f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"number60", numbertexture2, Vector2(41.5f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"number70", numbertexture2, Vector2(49.8f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"number80", numbertexture2, Vector2(58.1f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"number90", numbertexture2, Vector2(66.4f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"number00", numbertexture2, Vector2(74.7f, 0.0f), Vector2(8.3f, 17.0f), Vector2::Zero, 1, 0.3f);

		mAnimator->Play(L"number10", false);
	}
	NumberTens::~NumberTens()
	{
	}
	void NumberTens::Initalize()
	{
		GameObject::Initalize();

	}
	void NumberTens::Update()
	{
		GameObject::Update();

		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);

		mPlayerCoin = PlayerManager::GetPlayer()->GetCoin();
		SetNumber(mPlayerCoin);
	}
	void NumberTens::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void NumberTens::Render()
	{
		GameObject::Render();
	}

	void NumberTens::SetNumber(int number)
	{
		int tens = (number / 10) % 10;
		std::wstring animationName = L"number";

		if (tens == 0)
			animationName += L"00";
		else
			animationName += std::to_wstring(tens * 10);

		mAnimator->Play(animationName, false);
	}

}