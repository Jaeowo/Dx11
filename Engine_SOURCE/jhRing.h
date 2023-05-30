#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Animator;

	enum class eRingSet
	{
		Vertical,
		horizontal,
		Sloped
	};

	class Ring
		: public GameObject
	{
	public:
		Ring();
		virtual ~Ring();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		bool GetTouch() { return mIsTouch; }
		void SetTouch(bool istouch) { mIsTouch = istouch; }

		//State
		void Vertical();
		void Horizontal();
		void Sloped();

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetCount(bool onecount) { mOneCount = onecount; }

	private:
		Vector3 mPosition;
		bool mIsTouch;
		eRingSet mRingSet;
		Transform* mTransform;
		Animator* mAnimator;

		bool mOneCount;
		float mTotalTime;
	};
}