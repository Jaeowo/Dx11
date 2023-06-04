#include "jhHpBar.h"
#include "jhTransform.h"
#include "jhAnimator.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhPlayer.h"

namespace jh
{
	HpBar::HpBar()
		: mPosition(Vector3(0.0f, 0.0f, 0.0f))
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(2.5f, 0.35f, 1.0f));
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
		//mPlayer = dynamic_cast<Player*>(mTarget);
	}
	void HpBar::Update()
	{
		GameObject::Update();

		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mPosition);

		if (mPlayer == nullptr)
			mPlayer = dynamic_cast<Player*>(mTarget);

		if (mPlayer == nullptr)
			return;

		int hp = mPlayer->GetHp();
		float xRatio = (hp / 100.0f);

		// We need to apply xRatio to the scale of the image.
		Vector3 currentScale = mTransform->GetScale();
		mTransform->SetScale(Vector3(xRatio * currentScale.x, currentScale.y, currentScale.z));

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