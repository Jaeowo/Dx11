#pragma once
#include "jhGameObject.h"


namespace jh
{

	class Animator;
	class Transform;

	class Coin
		: public GameObject
	{
	public:
		Coin();
		virtual ~Coin();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetPosition(Vector3 position) { mPosition = position; }

		void SetCount(bool onecount) { mOneCount = onecount; }
		void Move(const Vector3& direction);

		void SetGround(bool bground) { mbGround = bground; }

		void SetSoundOn(bool soundon) { mSoundOn = soundon; }

	private:
		Vector3 mPosition;
		Vector3 mVelocity;
		Collider2D* mCollider;

		Animator* mAnimator;
		Transform* mTransform;

		bool mbGround;
		bool mOneCount;
		bool mSoundOn;
		float mSpeed;  
		float mGravity;  
		
	};
}


