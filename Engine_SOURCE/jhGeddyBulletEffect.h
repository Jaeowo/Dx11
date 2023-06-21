#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Animator;

	class GeddyBulletEffect
		: public GameObject
	{
	public:
		GeddyBulletEffect();
		virtual ~GeddyBulletEffect();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetPosition(Vector3 position) { mPosition = position; }

	private:
		Transform* mTransform;
		Animator* mAnimator;
		Vector3 mPosition;

		float mTime;
		bool mOneCount;
	};
}
