#include "jhGeddy.h"
#include "jhCollider2D.h"
#include "jhTransform.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhPlayerManager.h"
#include "jhPlayer.h"
#include "jhGeddyScript.h"

namespace jh
{
	Geddy::Geddy()
		: mbGround(false)
		, mCount(0)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(Vector3(0.9f, 0.86f, 1.7f));
		mTransform->SetScale(Vector3(0.35f, 0.35f, 1.0f));

		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetType(eColliderType::Rect);
		collider->SetSize(Vector2(0.1f, 0.28f));

		SpriteRenderer* geddysr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> geddymesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> geddymaterial = Resources::Find<Material>(L"Geddymaterial");
		geddysr->SetMaterial(geddymaterial);
		geddysr->SetMesh(geddymesh);


	}
	Geddy::~Geddy()
	{
	}
	void Geddy::Initalize()
	{
		GameObject::Initalize();
	}
	void Geddy::Update()
	{
		GameObject::Update();
		
	}
	void Geddy::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Geddy::Render()
	{
		GameObject::Render();
	}
}