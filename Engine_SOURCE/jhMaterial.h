#pragma once
#include "jhResource.h"
#include "jhShader.h"
#include "jhRenderer.h"
#include "jhConstantBuffer.h"


using namespace jh::renderer;
namespace jh::graphics
{
	class Material
		:public Resource
	{
	public:
		Material();
		~Material();

		virtual HRESULT Load(const std::wstring& path) override;

		void SetData(eGPUParam param, void* data);
		void Bind();

		void SetShader(Shader* shader) { mShader = shader; }
		Shader* GetShader() { return mShader; }
		
	private:
		Shader* mShader;
		MaterialCB mCB;
	};
}


