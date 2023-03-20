#pragma once
#include "jhScript.h"

namespace jh
{
	class Player;

	class PlayerScript
		: public Script
	{
	public:


		PlayerScript();
		~PlayerScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		//ePlayerState GetPlayerState() { return mPlayerState; }

		void Start();
		void Action();
		void End();

	private:
		ePlayerState mPlayerState;

		//Animator* mAnimator;

		float mGravity;

		bool mbGround;
		bool mbCarrying;


	};
}


