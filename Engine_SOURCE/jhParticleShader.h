#pragma once
#include "jhComputeShader.h"
#include "jhStructedBuffer.h"

namespace jh::graphics
{
	class ParticleShader
		: public ComputeShader
	{
	public:
		ParticleShader();
		~ParticleShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetStrcutedBuffer(StructedBuffer* buffer);

	private:
		StructedBuffer* mBuffer;
	};
}


