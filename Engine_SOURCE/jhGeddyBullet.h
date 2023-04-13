#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Animator;
	class Transform;

	class GeddyBullet
		: public GameObject
	{
	public:
		GeddyBullet();
		virtual ~GeddyBullet();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		Animator* mAnimator;
		Transform* mTransform;
	};
}


