#pragma once
#include "jhScene.h"

namespace jh
{
	class Player;

	class CaveScene2 : public Scene
	{
	public:
		CaveScene2();
		virtual ~CaveScene2();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		Player* mplayer;
	};
}