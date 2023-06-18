#include "jhStoneDoor.h"
#include "jhAnimator.h"
#include "jhResources.h"
#include "jhSpriteRenderer.h"
#include "jhStoneDoorScript.h"

namespace jh
{
	StoneDoor::StoneDoor()
		: mPosition(Vector3(0.0f, 0.0f, 0.0f))
		, mScale(Vector3(0.0f, 0.0f, 0.0f))
		, mOneCount(false)
		, mTotalTime(0.0f)
		, mDoorState (DoorState::Idle)
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mTransform->SetPosition(mPosition);
		mTransform->SetRotation(mRotation);
		mTransform->SetScale(mScale);

		SpriteRenderer* horizontalsr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> horizontalmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> horizontalmaterial = Resources::Find<Material>(L"Horizontalmaterial");
		horizontalsr->SetMaterial(horizontalmaterial);
		horizontalsr->SetMesh(horizontalmesh);

		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.2f, 1.1f));
		mCollider->SetCenter(mCenter);

		std::shared_ptr<Texture> StoneDoortexture1 = Resources::Load<Texture>(L"StonDoor1", L"MapObject\\sprStoneDoorClose_99x192_strip15.png");
		std::shared_ptr<Texture> StoneDoortexture2 = Resources::Load<Texture>(L"StoneDoor2", L"MapObject\\spr_StoneDoor_99x192_strip15.png");

		mAnimator->Create(L"IdleDoor", StoneDoortexture2, Vector2(0.0f, 0.0f), Vector2(99.0f, 192.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"OpenDoor", StoneDoortexture1, Vector2(0.0f, 0.0f), Vector2(99.0f, 192.0f), Vector2::Zero, 15, 0.3f);
		mAnimator->Create(L"CloseDoor", StoneDoortexture2, Vector2(0.0f, 0.0f), Vector2(99.0f, 192.0f), Vector2::Zero, 15, 0.3f);

		mAnimator->Play(L"IdleDoor", false);
	}
	StoneDoor::~StoneDoor()
	{
	}
	void StoneDoor::Initalize()
	{
		GameObject::Initalize();
		AddComponent<StoneDoorScript>();
	}
	void StoneDoor::Update()
	{
		GameObject::Update();

		mCollider = GetComponent<Collider2D>();
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);
		mTransform->SetRotation(mRotation);
		mTransform->SetScale(mScale);
		mCollider->SetCenter(mCenter);
	
		
		switch (mDoorState)
		{
		case jh::DoorState::Idle:
			Idle();
			break;
		case jh::DoorState::Close:
			Close();
			break;
		case jh::DoorState::Open:
			Open();
			break;
		default:
			break;
		}

	}
	void StoneDoor::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void StoneDoor::Render()
	{
		GameObject::Render();
	}

	void StoneDoor::Idle()
	{
	}

	void StoneDoor::Close()
	{
	}

	void StoneDoor::Open()
	{
	}

}