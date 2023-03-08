#include "jhAnimation.h"
#include "jhTime.h"

namespace jh
{
	Animation::Animation()
		: mAnimator(nullptr)
		, mAtlas(nullptr)
		, mSpriteSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{
	}
	Animation::~Animation()
	{
	}
	void Animation::Update()
	{
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();

		if (mSpriteSheet[mIndex].duration < mTime)
		{
			mTime = 0.0f;
			++mIndex; //다음 프레임
			
			if (mSpriteSheet.size() <= mIndex)
			{
				mbComplete = true;
				mIndex = mSpriteSheet.size() - 1;
			}

		}
	}
	void Animation::FixedUpdate()
	{
	}
	void Animation::Render()
	{
	}
	void Animation::Create(const std::wstring& name
		, std::shared_ptr<Texture> atlas
		, Vector2 leftTop, Vector2 size, Vector2 offset
		, UINT columnLength, UINT spriteLength, float duration)
	{
	}
	void Animation::BindShader()
	{
	}
	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}
	void Animation::Clear()
	{
	}
}