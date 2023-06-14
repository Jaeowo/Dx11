#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class Animator;
	class Collider2D;

	enum class DoorState
	{
		Idle,
		Close,
		Open,
	};

	class StoneDoor
		: public GameObject
	{
	public:
		StoneDoor();
		virtual ~StoneDoor();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		//State
		void Idle();
		void Close();
		void Open();

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetRotation(Vector3 rotation) { mRotation = rotation; }
		void SetScale(Vector3 scale) { mScale = scale; }
		void SetCenter(Vector2 center) { mCenter = center; }
		void SetCount(bool onecount) { mOneCount = onecount; }


	private:
		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;
		Vector2 mCenter;
		Transform* mTransform;
		Animator* mAnimator;
		Collider2D* mCollider;
		DoorState mDoorState;

		bool mOneCount;
		float mTotalTime;
	};
}