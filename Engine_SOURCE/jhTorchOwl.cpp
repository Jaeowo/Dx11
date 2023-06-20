#include "jhTorchOwl.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhAnimator.h"


namespace jh
{
	TorchOwl::TorchOwl()
		:mOneCount(false)
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


		std::shared_ptr<Texture> Torchowltexture = Resources::Load<Texture>(L"Torchowl", L"MapObject\\spr_TorchOwl_51x70.png");

		mAnimator->Create(L"Torchowl", Torchowltexture, Vector2(0.0f, 0.0f), Vector2(51.0f, 70.0f), Vector2::Zero, 1, 0.3f);


		mAnimator->Play(L"Torchowl", false);


	}
	TorchOwl::~TorchOwl()
	{
	}
	void TorchOwl::Initalize()
	{
		GameObject::Initalize();
	}
	void TorchOwl::Update()
	{
		GameObject::Update();
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);

	}
	void TorchOwl::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void TorchOwl::Render()
	{
		GameObject::Render();
	}


}