#pragma once
#include "yaGraphics.h"

using namespace ya::enums;

namespace ya::graphics
{
	class ConstantBuffer : GpuBuffer
	{
	public:
		ConstantBuffer();
		virtual ~ConstantBuffer();

		bool Create(size_t size);
		void Bind(void* data);
		void SetPipline(eShaderStage stage);

	private:
		const eCBType mType;
	};
}


