#pragma once
#include "jhEntity.h"
#include "jhTexture.h"

using namespace jh::math;
using namespace jh::graphics;

namespace jh
{
	class Animation
		: public Entity
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			Vector2 atlasSize;
			float duration;

			Sprite()
				: leftTop(0.0f, 0.0f)	// �»��
				, size(0.0f, 0.0f)		// �߶� ���� ���� ����
				, offset(0.0f, 0.0f)	// ������ ��ġ
				, atlasSize(0.0f)		// �ؽ�ó �̹����� ũ��
				, duration(0.1f)		// �ð�����
			{
			}
		};

		Animation();
		~Animation();

		UINT Update();
		void FixedUpdate();
		void Render();

		void Create(const std::wstring& name, std::shared_ptr<Texture> atlas
					, Vector2 leftTop, Vector2 size, Vector2 offset
					, UINT spriteLength, float duration);
		void BindShader();
		void Reset();
		void Clear();

		bool IsComplete() { return mbComplete; }
		std::wstring& AnimationName() { return mAnimationName; }

	private:
		class Animator* mAnimator;
		std::wstring mAnimationName;
		std::shared_ptr<Texture> mAtlas;
		std::vector<Sprite> mSpriteSheet;
		int mIndex;
		float mTime;
		bool mbComplete;
	};
}


