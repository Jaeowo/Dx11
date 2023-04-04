#pragma once
#include "jhComponent.h"

namespace jh
{
	using namespace math;
	class Rigidbody
		: public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void AddForce(Vector3 force);
		void SetMass(float mass) { mMass = mass; }
		void SetGround(bool isGround) { mbGround = isGround; }
		bool GetGround() { return mbGround; }

		Vector3 GetVelocity() { return mVelocity; }
		void SetVelocity(Vector3 velocity) { mVelocity = velocity; }

	private:
		// 힘과 마찰력을 이용한 이동
		float mMass;
		float mFriction;
		float mMoveFriction;
		Vector3 mForce;
		Vector3 mVelocity;
		Vector3 mAccelation;

		// 중력 이용한 점프
		Vector3 mGravity;
		bool mbGround;
		Vector3 mLimitVelocity;

	};
}


