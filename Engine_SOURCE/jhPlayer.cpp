#include "jhPlayer.h"
#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhCollider2D.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
namespace jh
{
	Player::Player()
		: mbGround(false)
		, mCount(0)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(Vector3(1.0f, 0.84f, 1.7f));
		mTransform->SetScale(Vector3(0.35f, 0.35f, 1.0f));

		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetType(eColliderType::Rect);
		collider->SetSize(Vector2(0.1f, 0.28f));
		//collider->SetCenter(Vector2(-0.015f, -0.02f));

		SpriteRenderer* standsr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> standmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> standmaterial = Resources::Find<Material>(L"Standmaterial");
		standsr->SetMaterial(standmaterial);
		standsr->SetMesh(standmesh);

		
	}
	Player::~Player()
	{
	}
	void Player::Initalize()
	{
		GameObject::Initalize();
	}
	void Player::Update()
	{

		GameObject::Update();
	}
	void Player::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Player::Render()
	{
		GameObject::Render();
	}
}