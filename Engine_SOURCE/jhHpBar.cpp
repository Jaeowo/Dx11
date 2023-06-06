#include "jhHpBar.h"
#include "jhTransform.h"
#include "jhAnimator.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhPlayer.h"
#include "jhPlayerManager.h"

namespace jh
{
	HpBar::HpBar()
		: mPosition(Vector3(0.0f, 0.0f, 0.0f))
		, mHp(0)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(3.5f, 0.35f, 1.0f));
		mTransform->SetPosition(mPosition);

		SpriteRenderer* hpsr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> hpmaterial = Resources::Find<Material>(L"HpMaterial");
		hpsr->SetMaterial(hpmaterial);
		hpsr->SetMesh(hpmesh);

		//mring = dynamic_cast<Ring*>(GetOwner());

	
	}
	HpBar::~HpBar()
	{
	}
	void HpBar::Initalize()
	{
		GameObject::Initalize();
		
	}
	void HpBar::Update()
	{
		GameObject::Update();

		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);

		mHp = PlayerManager::GetPlayer()->GetHp();
		float xRatio = (mHp / 3.0f);

		// We need to apply xRatio to the scale of the image.
		mTransform->SetScale(Vector3(xRatio, 0.3f, 1.0f));

	}
	void HpBar::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void HpBar::Render()
	{
		GameObject::Render();
	}

}