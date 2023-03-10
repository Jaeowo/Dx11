#include "jhAnimation.h"
#include "jhTime.h"
#include "jhRenderer.h"

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
	UINT Animation::Update()
	{
		if (mbComplete)
			return -1;

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
			return mIndex;
		}

		return -1;
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
		, UINT spriteLength, float duration)
	{
		mAnimationName = name;

		mAtlas = atlas;
		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();

		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite = {};
			sprite.leftTop = Vector2((leftTop.x + (size.x * (float)i)) / width, (leftTop.y) / height);
			sprite.size = Vector2(size.x / width, size.y / height);
			sprite.offset = offset;
			sprite.duration = duration;
			sprite.atlasSize = Vector2(200.0f / width, 200.0f / height);

			mSpriteSheet.push_back(sprite);
		}
	}
	void Animation::BindShader()
	{
		mAtlas->BindShader(eShaderStage::PS, 12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];

		renderer::AnimationCB info = {};
		info.type = (UINT)eAnimationType::SecondDimension;
		info.leftTop = mSpriteSheet[mIndex].leftTop;
		info.offset = mSpriteSheet[mIndex].offset;
		info.size = mSpriteSheet[mIndex].size;
		info.atlasSize = mSpriteSheet[mIndex].atlasSize;

		cb->Bind(&info);
		cb->SetPipline(eShaderStage::PS);
	}
	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}
	void Animation::Clear()
	{
		Texture::Clear(12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];
		renderer::AnimationCB info = {};
		info.type = (UINT)eAnimationType::None;

		cb->Bind(&info);
		cb->SetPipline(eShaderStage::PS);
	}
}