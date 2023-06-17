#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Animator;

	enum class eBeeHiveState
	{
		Idle,
		SpawnBees,
		Fallen,
	};

	class BeeHive
		: public GameObject
	{
	public:
		BeeHive();
		virtual ~BeeHive();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		//State

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