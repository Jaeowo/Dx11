#pragma once
#include "jhBaseRenderer.h"
#include "jhParticleShader.h"

namespace jh
{
	class ParticleSystem
		: public BaseRenderer
	{
		enum class eSimulationSpace
		{
			Local,
			World,
		};

	public:
		ParticleSystem();
		~ParticleSystem();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:
		class StructedBuffer* mBuffer;
		class StructedBuffer* mSharedBuffer;

		std::shared_ptr<graphics::ParticleShader> mCS;
		renderer::ParticleSystemCB mCBData;

		Vector4 mStartSize;
		Vector4 mStartColor;

		eSimulationSpace mSimulationSpace;
		UINT mMaxParticles;
		float mStartLifeTime;
		float mFrequency;
		float mRadius;

		float mStartSpeed;
		float mTime;
		float mElapsedTime; //�����ð�
	};
}


