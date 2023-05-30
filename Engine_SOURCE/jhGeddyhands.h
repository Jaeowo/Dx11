#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Animator;
	class Transform;

	enum class eGeddyhandsState
	{
		Stop,
		Shoot,
	};

	class Geddyhands
		: public GameObject
	{
	public:
		Geddyhands();
		virtual ~Geddyhands();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		eGeddyhandsState GetPlayerState() { return mGeddyhandsState; }
		void SetPlayerState(eGeddyhandsState geddyhandsstate) { mGeddyhandsState = geddyhandsstate; }

		Vector3 GetGeddyHandsPos() { return mPos; }

		void SetCount(UINT count) { mCount = count; }

		//State
		void Shoot();
		void Stop();

	private:
		eGeddyhandsState mGeddyhandsState;
		Animator* mAnimator;
		Transform* mTransform;
		Transform* mGeddyTransform;
		Vector3 mAngle;
		Vector2 mMousePos;
		Vector3 mPos;
		UINT mCount;
		float mTime;

		Transform* mArmTransform;
		float mArmLength = 0.1f;
		Vector3 mRestPosition = Vector3(-0.05f, -0.105f, 0.0f);

	};
}


