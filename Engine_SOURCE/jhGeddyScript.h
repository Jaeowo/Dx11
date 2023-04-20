#pragma once
#include "jhScript.h"


namespace jh
{
	class Animator;
	class Transform;



	class GeddyScript
		: public Script
	{
	public:

		GeddyScript();
		~GeddyScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		//status
		void Idle();
		void Hanging();


	private:
		Animator* mAnimator;
		Transform* mTransform;

		eGeddyState mGeddyState;
		int mCount;
	};
}


