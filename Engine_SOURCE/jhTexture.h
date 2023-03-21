#pragma once
#include "jhResource.h"
#include "..\External\DirectXTex\Include\DirectXTex.h"

#include "jhGraphicDevice_DX11.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\lib\\Debug\\DirectXTex.lib") 
#else 
#pragma comment(lib, "..\\External\\DirectXTex\\lib\\Release\\DirectXTex.lib") 
#endif

using namespace jh::enums;
namespace jh::graphics
{
	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		static void Clear(UINT startSlot);

		bool Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag);
		virtual HRESULT Load(const std::wstring& path) override;
		void BindShader(eShaderStage stage, UINT slot);
		void Clear();

		size_t GetHeight() { return mImage.GetMetadata().height; }
		size_t GetWidth() { return mImage.GetMetadata().width; }

		Microsoft::WRL::ComPtr<ID3D11Texture2D> GetTexture() { return mTexture; }
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDSV() { return mDSV; }
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRTV() { return mRTV; }
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> GetUAV() { return mUAV; }
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSRV() { return mSRV; }

	private:
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDSV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRTV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mUAV;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		D3D11_TEXTURE2D_DESC mDesc;
	};
}


