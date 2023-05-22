#include "jhSlope.h"
#include "jhSlopeScript.h"
#include "jhTransform.h"

namespace jh
{
	Slope::Slope()
		:mLeftUp(false)
		,mRightUp(false)
	{
		AddComponent<SlopeScript>();
		Collider2D* groundcollider = AddComponent<Collider2D>();
		groundcollider->SetType(eColliderType::Rect);

		mslopescript = AddComponent<SlopeScript>();
		mslopescript->SetSlope(this);

	}
	Slope::~Slope()
	{
	}
	void Slope::Initalize()
	{
		GameObject::Initalize();

	}
	void Slope::Update()
	{
		GameObject::Update();
		Transform* slopeTr = GetComponent<Transform>();
		if (mLeftUp == true)
		{
			slopeTr->SetRotation(Vector3(0.0f, 0.0f, 310.0f));
		}
		else if (mRightUp == true)
		{
			slopeTr->SetRotation(Vector3(0.0f, 0.0f, 55.0f));
		}
	}
	void Slope::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Slope::Render()
	{
		GameObject::Render();
	}
}