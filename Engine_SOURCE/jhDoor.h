#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Collider2D;

	class Door
		: public GameObject
	{
	public:
		Door();
		virtual ~Door();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetColPos(Vector3 ColPos) { mColPos = ColPos; }
		Vector3 GetColPos() { return mColPos; }

		void SetColSize(Vector2 ColSize) { mColSize = ColSize; }
		Vector2 GetColSize() { return mColSize; }

	private:
		Collider2D* mCollider2D;
		Vector3 mColPos;
		Vector2 mColSize;
	};
}