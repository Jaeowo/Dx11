#pragma once
#include "jhComponent.h"
#include "jhGraphics.h"

namespace jh
{
	class Light : public Component
	{
	public:
		enum class LightState
		{
			Idle,
			ChangingColor,
			FadingOut
		};

	public:
		Light();
		~Light();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		graphics::LightAttribute GetLightAttribute() { return mAttribute; }

		void SetDiffuse(Vector4 diffuse) { mAttribute.diffuse = diffuse; }
		void SetAmbient(Vector4 ambient) { mAttribute.ambient = ambient; }
		void SetType(eLightType type) { mAttribute.type = type; }
		void SetRadius(float radius) { mAttribute.radius = radius; }
		void SetAngle(float angle) { mAttribute.angle = angle; }
		Vector4 GetDiffuse() { mAttribute.diffuse; }
		eLightType GetType() { return mAttribute.type; }
		float GetRadius() { mAttribute.radius; }
		float GetAngle() { mAttribute.angle; }

		void ChangeColorOverTime(float duration, Vector4 startColor, Vector4 endColor);
		void FadeOut(float startTime);

	private:
		graphics::LightAttribute mAttribute;

	private:
		LightState mState;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float mChangeColorDuration;
		float mChangeColorStartTime;
		float mFadeOutStartTime;
		float mTotalTime;
	};
}


