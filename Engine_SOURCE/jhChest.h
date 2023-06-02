#pragma once
#include "jhGameObject.h"

namespace jh
{

	class Animator;
	class Transform;

	enum class eChestState
	{
		Idle,
		Open,
		Hanging,
		Finish,
	};

	class Chest
		: public GameObject
	{
	public:
		Chest();
		virtual ~Chest();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void PlayOpen2Animation();
		void PlayFinishAnimation();
		void SpawnCoin(int coinCount);

		void SetPosition(Vector3 position) { mPosition = position; }

		void SetCount(bool onecount) { mOneCount = onecount; }

		void SetState(eChestState cheststate) { mChestState = cheststate; }

		//State
		void Idle();
		void Open();
		void Hanging();
		void Finish();

	private:
		Vector3 mPosition;
		Vector3 mPlayerPosition;

		Collider2D* mCollider;
		Animator* mAnimator;
		Transform* mTransform;
		Transform* mPlayerTransform;

		float mElpasedTime;

		eChestState mChestState;
		bool mOpen;
		bool mOneCount;
		bool mIsOpen2Played;
		bool mIsOpenFinishPlayed;
	};
}

