#pragma once
#include "jhGraphics.h"

using namespace jh::enums;

namespace jh::graphics
{
	class ConstantBuffer : GpuBuffer
	{
	public:
		ConstantBuffer(eCBType type);
		virtual ~ConstantBuffer();

		bool Create(size_t size);
		void SetData(void* data);
		void Bind(eShaderStage stage);

		//void SetType(eCBType type) { mType = type; }

	private:
		const eCBType mType;
	};
}


