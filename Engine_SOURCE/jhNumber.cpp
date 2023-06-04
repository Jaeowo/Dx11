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
		//mAnimator = AddComponent<Animator>();
		//mTransform = GetComponent<Transform>();

		//mTransform->SetScale(Vector3(0.3f, 0.3f, 1.0f));
		//mTransform->SetPosition(mPosition);
		//SpriteRenderer* horizontalsr = AddComponent<SpriteRenderer>();
		//std::shared_ptr<Mesh> horizontalmesh = Resources::Find<Mesh>(L"RectMesh");
		//std::shared_ptr<Material> horizontalmaterial = Resources::Find<Material>(L"Horizontalmaterial");
		//horizontalsr->SetMaterial(horizontalmaterial);
		//horizontalsr->SetMesh(horizontalmesh);

		//std::shared_ptr<Texture> ringwoodtexture = Resources::Load<Texture>(L"RingWood", L"Rings\\ring_wood.png");
		//std::shared_ptr<Texture> ringwoodtexture2 = Resources::Load<Texture>(L"RingWood2", L"Rings\\ring_wood.png");

		//mAnimator->Create(L"Vertical", ringwoodtexture, Vector2(0.0f, 0.0f), Vector2(115.0f, 115.0f), Vector2::Zero, 1, 0.3f);
		//mAnimator->Create(L"Horizontal", ringwoodtexture, Vector2(0.0f, 115.0f), Vector2(115.0f, 115.0f), Vector2::Zero, 1, 0.3f);
		//mAnimator->Create(L"Sloped", ringwoodtexture, Vector2(0.0f, 230.0f), Vector2(115.0f, 115.0f), Vector2::Zero, 1, 0.3f);

		//mAnimator->Play(L"Sloped", false);

		//Collider2D* mCollider = AddComponent<Collider2D>();
		//mCollider->SetType(eColliderType::Rect);
		//mCollider->SetSize(Vector2(0.1f, 0.1f));



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