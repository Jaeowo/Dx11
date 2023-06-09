#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Animator;

	class TortoiseMask
		: public GameObject
	{
	public:
		TortoiseMask();
		virtual ~TortoiseMask();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetCount(bool onecount) { mOneCount = onecount; }

	private:
		Vector3 mPosition;
		Transform* mTransform;
		Animator* mAnimator;

		bool mOneCount;
		float mTotalTime;
	};
}