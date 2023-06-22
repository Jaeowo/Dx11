#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Animator;

	class BigDustEffect
		: public GameObject
	{
	public:
		BigDustEffect();
		virtual ~BigDustEffect();

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
