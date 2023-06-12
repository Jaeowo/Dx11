#pragma once
class EventTriggerScript
{
};

#include "jhScript.h"

namespace jh
{
	class EventTrigger;

	class EventTriggerScript
		: public Script
	{
	public:

		EventTriggerScript();
		~EventTriggerScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

	private:
		EventTrigger* meventtrigger;
	};
}
