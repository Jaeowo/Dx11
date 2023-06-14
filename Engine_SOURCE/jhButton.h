#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Animator;
	class Collider2D;

	enum class eButtonState
	{
		Idle,
		Press,
		UnPress,
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
		void Close();
		void Open();

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetCount(bool onecount) { mOneCount = onecount; }


	private:
		Vector3 mPosition;
		Transform* mTransform;
		Animator* mAnimator;
		Collider2D* mCollider;
		eButtonState mButtonState;

		bool mOneCount;
		float mTotalTime;
	};
}