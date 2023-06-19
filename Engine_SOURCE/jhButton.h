#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Animator;
	class Collider2D;
	class StoneDoor;

	enum class eButtonState
	{
		Idle,
		Press,
		PressIdle
	};

	class Button
		: public GameObject
	{
	public:
		Button();
		virtual ~Button();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		//State
		void Idle();
		void Press();
		void PressIdle();

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetCount(bool onecount) { mOneCount = onecount; }
		void SetPressTrigger(bool presstrigger) { mPressTrigger = presstrigger; }

	private:
		Vector3 mPosition;
		Transform* mTransform;
		Animator* mAnimator;
		Collider2D* mCollider;
		StoneDoor* mStonedoor;

		eButtonState mButtonState;

		bool mOneCount;
		bool mPressTrigger;
		bool mPressOneCheck;
		float mTotalTime;
	};
}