#pragma once
#include "jhScript.h"

namespace jh
{
	class Collider2D;

	class DoorScript
		: public Script
	{
	public:

		DoorScript();
		~DoorScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

	private:
		Collider2D* mCollider;
		Vector3 mColPos;
		int mCount;
		float mElapsedTime;
	};
}