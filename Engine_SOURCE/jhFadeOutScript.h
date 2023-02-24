#pragma once
#include "jhScript.h"

namespace jh
{
	class FadeOutScript
		: public Script
	{
	public:
		FadeOutScript();
		virtual ~FadeOutScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		float mAmount;

	};
}
