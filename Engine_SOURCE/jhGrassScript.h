#pragma once
#include "jhScript.h"

namespace jh
{
	class GrassScript
		: public Script
	{
	public:

		GrassScript();
		~GrassScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

	private:
		Vector3 mLastPlayerPos;
		float mParallax;
	};
}
