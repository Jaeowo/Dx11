#include "jhLight.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhRenderer.h"
#include "jhTime.h"

namespace jh
{
	Light::Light()
		: Component(eComponentType::Light)
		, mTotalTime(0.0f)
	{

	}

	Light::~Light()
	{

	}

	void Light::Initalize()
	{

	}

	void Light::Update()
	{
		mTotalTime += Time::DeltaTime();

		switch (mState)
		{
		case LightState::ChangingColor:
		{
			float t = (mTotalTime - mChangeColorStartTime) / mChangeColorDuration;
			if (t >= 1.0f)
			{
				mState = LightState::Idle;
				SetDiffuse(mEndColor);
			}
			else
			{
				Vector4 currentColor = Vector4::Lerp(mStartColor, mEndColor, t);
				SetDiffuse(currentColor);
			}
			break;
		}

		case LightState::FadingOut:
		{
			if (mTotalTime >= mFadeOutStartTime)
			{
				mState = LightState::Idle;
				SetRadius(0.0f);
			}
			break;
		}

		default: break;
		}

	}

	void Light::FixedUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 position = tr->GetPosition();
		mAttribute.position = Vector4(position.x, position.y, position.z, 1.0f);
		mAttribute.direction = Vector4(tr->Right().x, tr->Right().y, tr->Right().z, 1.0f);

		renderer::lights.push_back(mAttribute);
	}

	void Light::Render()
	{

	}
	void Light::ChangeColorOverTime(float duration, Vector4 startColor, Vector4 endColor)
	{
		mState = LightState::ChangingColor;
		mStartColor = startColor;
		mEndColor = endColor;
		mChangeColorDuration = duration;
		mChangeColorStartTime = mTotalTime;
	}

	void Light::FadeOut(float startTime)
	{
		mState = LightState::FadingOut;
		mFadeOutStartTime = startTime + mTotalTime;
	}
}