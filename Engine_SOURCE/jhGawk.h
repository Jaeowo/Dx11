#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Animator;
	class Transform;

	enum class eGawkState
	{
		Flying,
		UpsideDown,
		UpsideDowntoFly,
		Hurt,
		Sturn,
	};

	class Gawk
		: public GameObject
	{
	public:
		Gawk();
		virtual ~Gawk();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	//State
		void Flying();
		void UpsideDown();
		void UpsideDowntoFly();
		void Hurt();
		void Sturn();

	//Get Set
		eGawkState GetPlayerState() { return mGawkState; }
		void SetPlayerState(eGawkState gawkstate) { mGawkState = gawkstate; }

		void SetHp(int hp) { mHp = hp; }

	private:
		Animator* mAnimator;
		Transform* mTransform;
		eGawkState mGawkState;

		int mCount;

	private:
		Vector3 mTargetPosition;
		Vector3 mMonsterPosition;
		bool mTarget;
		int mHp;
	};
}


