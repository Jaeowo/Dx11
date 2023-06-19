#pragma once
#include "jhScript.h"

namespace jh
{
	class Aegis;

	class AegisScript
		: public Script
	{
	public:

		AegisScript();
		~AegisScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

	private:
		Aegis* mAegis;
	};
}
