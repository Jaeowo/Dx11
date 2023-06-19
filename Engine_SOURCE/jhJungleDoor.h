#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Collider2D;
	class Transform;
	class Animator;

	class JungleDoor
		: public GameObject
	{
	public:
		JungleDoor();
		virtual ~JungleDoor();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetColPos(Vector3 ColPos) { mColPos = ColPos; }
		Vector3 GetColPos() { return mColPos; }

		void SetColSize(Vector2 ColSize) { mColSize = ColSize; }
		Vector2 GetColSize() { return mColSize; }

		void SetCavetoCave2(bool cavecave) { mCavetoCave2 = cavecave; }
		bool GetCavetoCave2() { return mCavetoCave2; }

		void SetCave2toJungle(bool cavejungle) { mCave2toJungle = cavejungle; }
		bool GetCave2toJungle() { return mCave2toJungle; }

		void SetPosition(Vector3 position) { mPosition = position; }

	private:
		Transform* mTransform;
		Animator* mAnimator;
		Collider2D* mCollider;
		Vector3 mPosition;

		Vector3 mColPos;
		Vector2 mColSize;

		bool mCavetoCave2;
		bool mCave2toJungle;

		bool mOneCount;
	};
}
