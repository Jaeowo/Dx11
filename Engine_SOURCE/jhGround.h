#pragma once
#include "jhGameObject.h"


namespace jh
{
	

	class Ground
		: public GameObject
	{
	public:
		Ground();
		virtual ~Ground();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetColPos(Vector2 ColPos) { mColPos = ColPos; }
		Vector2 GetColPos() { return mColPos; }

		void SetColSize(Vector2 ColSize) { mColSize = ColSize; }
		Vector2 GetColSize() { return mColSize; }

	private:
		Collider2D* mCollider2D;
		Vector2 mColPos;
		Vector2 mColSize;
	};
}


