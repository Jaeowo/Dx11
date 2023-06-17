#include "jhTortoiseMask.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhAnimator.h"
#include "jhTime.h"

namespace jh
{
	TortoiseMask::TortoiseMask()
		: mPosition(Vector3(0.0f, 0.0f, 0.0f))
		, mOneCount(false)
		, mTime(0.0f)
		, mInitialVelocity(Vector2(0.0f, 0.00038f))
		, mGravity (0.0007f)
		, mLeft(false)
		, mRight(false)
		, mHorizontalSpeed(0.1f)
		, mVelocity(0.0f, 0.0f, 0.0f)
		, mbGround(false)
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
			Vector2(0.0f, 0.0f), Vector2(129.0f, 124.0f), Vector2::Zero, 9, 0.4f);

		mAnimator->Play(L"ThrowMask", false);

		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.2f, 0.2f));
		//mCollider->SetCenter(Vector2(0.0f, -0.02f));

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

		mPosition += mVelocity * Time::DeltaTime();

		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);

		mTime += Time::DeltaTime();

		if (mbGround == true)
		{
			mGravity = 0.0f;
			mVelocity = Vector3(0.0f, 0.0f, 0.0f);
			
		}
		else
		{
			Vector2 pos2D = Vector2(mPosition.x, mPosition.y);

			if (mLeft == true)
			{
				pos2D.x -= mHorizontalSpeed * mTime / 620.0f;
			}
			if (mRight == true)
			{
				pos2D.x += mHorizontalSpeed * mTime / 620.0f;
			}

			mVelocity.y = mInitialVelocity.y * mTime - 0.5f * mGravity * mTime * mTime;

			pos2D.y += mVelocity.y;

			mPosition = Vector3(pos2D.x, pos2D.y, mPosition.z);

			mTransform->SetPosition(mPosition);
		}
	}
	void TortoiseMask::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void TortoiseMask::Render()
	{
		GameObject::Render();
	}
	void TortoiseMask::ReverseDirection()
	{
		mLeft = !mLeft;
		mRight = !mRight;
	}
}