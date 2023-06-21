#pragma once
#include "jhScene.h"

namespace jh
{
	class Player;
	class AudioSource;

	class JungleScene : public Scene
	{
	public:
		JungleScene();
		virtual ~JungleScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		Player* mplayer;
		AudioSource* maudioSource;
	};
}