#pragma once
#include "jhScript.h"

namespace jh
{
	class PlayerScript
		: public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;
	private:

	};
}


