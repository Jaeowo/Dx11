#pragma once

#include "jhScript.h"

namespace jh
{
	class Collider2D;
	class Slope;

	class SlopeScript
		: public Script
	{
	public:

		SlopeScript();
		~SlopeScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;
		void SetSlope(Slope* slope) { this->mslope = slope; }

	private:
		Collider2D* mCollider;
		Vector3 mColPos;
		int mCount;
		Slope* mslope;  

		
	};
}