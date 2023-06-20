#include "jhTorch.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhAnimator.h"
#include "jhLight.h"
#include "jhObject.h"

namespace jh
{
	Torch::Torch()
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


		std::shared_ptr<Texture> Torchtexture = Resources::Load<Texture>(L"Torch", L"MapObject\\spr_TorchOnTrack_40x50.png");

		mAnimator->Create(L"Fire", Torchtexture, Vector2(0.0f, 100.0f), Vector2(40.0f, 50.0f), Vector2::Zero, 3, 0.3f);


		mAnimator->Play(L"Fire", true);



	}
	Torch::~Torch()
	{
	}
	void Torch::Initalize()
	{
		GameObject::Initalize();
	}
	void Torch::Update()
	{
		GameObject::Update();
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);

		if (mOneCount == false)
		{

			GameObject* pointLight = object::Instantiate<GameObject>(eLayerType::Effect);
			pointLight->GetComponent<Transform>()->SetPosition(mTransform->GetPosition());

			Light* lightComp = pointLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(0.35f);

			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 0.6f));

			mOneCount = true;
		}

	}
	void Torch::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Torch::Render()
	{
		GameObject::Render();
	}


}