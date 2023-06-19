#include "jhJungleDoor.h"
#include "jhJungleDoorScript.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhAnimator.h"

namespace jh
{
	JungleDoor::JungleDoor()
		: mCavetoCave2(false)
		, mCave2toJungle(false)
		, mOneCount(false)
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

		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.3f, 0.4f));

		std::shared_ptr<Texture> JungleDoortexture = Resources::Load<Texture>(L"JungleDoor", L"MapObject\\sprDoorsDungeon2_70x75.png");

		mAnimator->Create(L"Cave2toJungle", JungleDoortexture, Vector2(0.0f, 0.0f), Vector2(70.0f, 75.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"CavetoCave2", JungleDoortexture, Vector2(140.0f, 0.0f), Vector2(70.0f, 75.0f), Vector2::Zero, 1, 0.3f);

		mAnimator->Play(L"Cave2toJungle", false);


	}
	JungleDoor::~JungleDoor()
	{
	}
	void JungleDoor::Initalize()
	{
		GameObject::Initalize();
		AddComponent<JungleDoorScript>();
	}
	void JungleDoor::Update()
	{
		GameObject::Update();

		mCollider = GetComponent<Collider2D>();
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);

		SetCave2toJungle(mCave2toJungle);
		SetCavetoCave2(mCavetoCave2);

		if (mCave2toJungle == true)
		{
			if (mOneCount == false)
			{
				mAnimator->Play(L"Cave2toJungle", false);
				mOneCount = true;
			}
		}
		else if (mCavetoCave2 == true)
		{
			if (mOneCount == false)
			{
				mAnimator->Play(L"CavetoCave2", false);
				mOneCount = true;
			}
		}
	}
	void JungleDoor::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void JungleDoor::Render()
	{
		GameObject::Render();
	}


}