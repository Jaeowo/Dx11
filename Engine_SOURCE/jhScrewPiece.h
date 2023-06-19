#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Animator;

	class ScrewPiece
		: public GameObject
	{
	public:
		ScrewPiece();
		virtual ~ScrewPiece();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetCount(bool onecount) { mOneCount = onecount; }


	private:
		Vector3 mPosition;
		Vector3 mTargetPosition;
		Transform* mTransform;
		Animator* mAnimator;
		Vector3 mRotation;

		bool mOneCount;
		float mTotalTime;
	};
}