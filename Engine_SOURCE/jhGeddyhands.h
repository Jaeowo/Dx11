#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Animator;
	class Transform;

	class Geddyhands
		: public GameObject
	{
	public:
		Geddyhands();
		virtual ~Geddyhands();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		Animator* mAnimator;
		Transform* mTransform;
		Vector3 mAngle;
		Vector2 mMousePos;
		Vector3 mPos;
	};
}


