#include "jhButton.h"
#include "jhAnimator.h"
#include "jhResources.h"
#include "jhSpriteRenderer.h"

namespace jh
{
	Button::Button()
		: mPosition(Vector3(0.0f, 0.0f, 0.0f))
		, mOneCount(false)
		, mTotalTime(0.0f)
		, mButtonState(eButtonState::Idle)
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mTransform->SetPosition(mPosition);
		mTransform->SetScale(Vector3(0.3f,0.3f,1.0f));

		SpriteRenderer* horizontalsr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> horizontalmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> horizontalmaterial = Resources::Find<Material>(L"Horizontalmaterial");
		horizontalsr->SetMaterial(horizontalmaterial);
		horizontalsr->SetMesh(horizontalmesh);

		Collider2D* mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.2f, 0.1f));

		std::shared_ptr<Texture> HeavyButtontexture = Resources::Load<Texture>(L"Button", L"MapObject\\spr_HeavyButton_76x43.png");

		mAnimator->Create(L"Idle", HeavyButtontexture, Vector2(0.0f, 0.0f), Vector2(76.0f, 43.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Create(L"Press", HeavyButtontexture, Vector2(0.0f, 86.0f), Vector2(76.0f, 43.0f), Vector2::Zero, 3, 0.3f);
		mAnimator->Create(L"PressIdle", HeavyButtontexture, Vector2(0.0f, 129.0f), Vector2(76.0f, 43.0f), Vector2::Zero, 4, 0.3f);


		mAnimator->Play(L"Idle", false);

	}
	Button::~Button()
	{
	}
	void Button::Initalize()
	{
		GameObject::Initalize();
	}
	void Button::Update()
	{
		GameObject::Update();

		mCollider = GetComponent<Collider2D>();
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);


	}
	void Button::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Button::Render()
	{
		GameObject::Render();
	}

	void Button::Idle()
	{
	}

	void Button::Close()
	{
	}

	void Button::Open()
	{
	}

}