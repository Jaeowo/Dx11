#pragma once
#include "jhScene.h"

namespace jh
{
	class Tortoise;
	class Player;

	class CaveScene : public Scene
	{
	public:
		CaveScene();
		virtual ~CaveScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		Tortoise* mtortoise;
		Player* mplayer;

		bool mCount;
	};
}
