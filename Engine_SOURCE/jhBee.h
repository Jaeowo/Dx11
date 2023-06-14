#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Animator;

	enum class BeeState
	{
		Idle,
		Attack,
		HitWall,
		Hit,
		Death,
	};

	class Bee
		: public GameObject
	{
	public:
		Bee();
		virtual ~Bee();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		//State
		void Idle();
		void Attack();
		void HitWall();
		void Hit();
		void Death();

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