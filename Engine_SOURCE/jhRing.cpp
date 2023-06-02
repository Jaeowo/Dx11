#include "jhRing.h"
#include "jhAnimator.h"
#include "jhResources.h"
#include "jhSpriteRenderer.h"
#include "jhLight.h"
#include "jhTransform.h"
#include "jhCollider2D.h"
#include "jhRingScript.h"
#include "jhObject.h"
#include "jhTime.h"

namespace jh
{
	Ring::Ring()
		: mIsTouch(false)
		, mRingSet(eRingSet::Vertical)
		, mPosition (Vector3(0.0f,0.0f,0.0f))
		, mOneCount(false)
		, mTotalTime(0.0f)
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mTransform->SetScale(Vector3(0.3f, 0.3f, 1.0f));
		mTransform->SetPosition(mPosition);
		SpriteRenderer* horizontalsr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> horizontalmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> horizontalmaterial = Resources::Find<Material>(L"Horizontalmaterial");
		horizontalsr->SetMaterial(horizontalmaterial);
		horizontalsr->SetMesh(horizontalmesh);

		std::shared_ptr<Texture> ringwoodtexture = Resources::Load<Texture>(L"RingWood", L"Rings\\ring_wood.png");
		std::shared_ptr<Texture> ringwoodtexture2 = Resources::Load<Texture>(L"RingWood2", L"Rings\\ring_wood.png");

		mAnimator->Create(L"Vertical", ringwoodtexture, Vector2(0.0f, 0.0f), Vector2(115.0f, 115.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"Horizontal", ringwoodtexture, Vector2(0.0f, 115.0f), Vector2(115.0f, 115.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"Sloped", ringwoodtexture, Vector2(0.0f, 230.0f), Vector2(115.0f, 115.0f), Vector2::Zero, 1, 0.3f);

		mAnimator->Play(L"Sloped", false);
	
		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.1f, 0.1f));

	}
	Ring::~Ring()
	{
	}
	void Ring::Initalize()
	{
		AddComponent<RingScript>();
		GameObject::Initalize();
	}
	void Ring::Update()
	{
		GameObject::Update();

		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);

		if (mIsTouch == true && mOneCount == false)
		{
			GameObject* pointLight = object::Instantiate<GameObject>(eLayerType::Player);
			pointLight->GetComponent<Transform>()->SetPosition(mTransform->GetPosition());

			Light* lightComp = pointLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(0.07f);

			lightComp->SetDiffuse(Vector4(0.0f, 1.0f, 0.0f, 1.0f));

			//동작 제대로 안하는데 함 확인해보기
			lightComp->ChangeColorOverTime(2.0f, Vector4(0.0f, 1.0f, 0.0f, 1.0f), Vector4(1.0f, 0.0f, 1.0f, 1.0f));

			mOneCount = true;

			mTotalTime += Time::DeltaTime();

			//this->Death();

			if (mTotalTime >= 2.0f)
			{
				//Death();
			}
		}

		

		switch (mRingSet)
		{
		case jh::eRingSet::Vertical:
			Vertical();
			break;
		case jh::eRingSet::horizontal:
			Horizontal();
			break;
		case jh::eRingSet::Sloped:
			Sloped();
			break;
		default:
			break;
		}

	}
	void Ring::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Ring::Render()
	{
		GameObject::Render();
	}
	void Ring::Vertical()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Vertical", false);
			mOneCount = true;
		}
	}
	void Ring::Horizontal()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Horizontal", false);
			mOneCount = true;
		}
	}
	void Ring::Sloped()
	{
		if (mOneCount == false)
		{
			mAnimator->Play(L"Sloped", false);
			mOneCount = true;
		}

	}
}