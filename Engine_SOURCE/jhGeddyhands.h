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

	private:
		eGeddyhandsState mGeddyhandsState;
		Animator* mAnimator;
		Transform* mTransform;
		Vector3 mAngle;
		Vector2 mMousePos;
		Vector3 mPos;

	};
}


