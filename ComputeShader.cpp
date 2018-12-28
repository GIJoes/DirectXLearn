#include<stdio.h>
#include<crtdbg.h>
#include<d3d11.h>
#include<d3dcommon.h>
#include<d3dx11.h>

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(P) {if(p) {(p)->Release(); (p)=NULL}}
#endif // !SAFE_RELEASE
/////
#define USE_STRUCTURED_BUFFERS
const UINT NUMELEMENTS = 1024;

HRESULT CreateComputeDevice(ID3D11Device**ppDeviceOut,ID3D11DeviceContext** ppContextOut,BOOL bForceCrt);
HRESULT CreateComputeShader(LPWSTR pSrcFile,LPSTR pFunctionName,
                                                         ID3D11Device*pDevice,ID3D11ComputeShader**ppComputeShader);
HRESULT CreateStructuredBuffer(ID3D11Device*pDevice,UINT uElementSize,UINT uSize,VOID*pInitData,ID3D11Buffer**ppBufOut);
HRESULT CreateRawBuffer(ID3D11Device*pDevice,UINT uSize,VOID*pInitData,ID3D11Buffer**ppBufOut);
HRESULT CreateBufferSRV(ID3D11Device*pDevice,ID3D11Buffer*pBuffer,ID3D11ShaderResourceView**ppSRVOut);
HRESULT CreateBufferUAV(ID3D11Device*pDevice,ID3D11Buffer*pBuffer,ID3D11UnorderedAccessView**ppUAVOut);
ID3D11Buffer*CreateAndCopyToDebugBuf(ID3D11Device*pDevice,ID3D11DeviceContext*pContext,ID3D11Buffer*pBuffer);
void RunComputeShader(ID3D11DeviceContext*pd3d11ImediateContext,
	                                     ID3D11ComputeShader*pComputeShader,
	UINT uNumViews,ID3D11ShaderResourceView*pShaderResourceView,
	ID3D11Buffer*pCBCS,void*pCSData,DWORD dwNumDataBytes,
	ID3D11UnorderedAccessView*pUnorderedAccessView,
	UINT X,UINT Y,UINT Z);
HRESULT FindDXSDKShaderFileCch(__in_ecount(cchDest)WCHAR*pStrDestPath,
	int cchDest,
	__in LPCWSTR strFileName);

//Global Value
ID3D11Device*                             g_pDevice=NULL;
ID3D11DeviceContext*                g_pContext = NULL;
ID3D11ComputeShader*              g_pCS = NULL;

ID3D11Buffer*                             g_pBuffer0 = NULL;
ID3D11Buffer*                             g_pBuffer1 = NULL;
ID3D11Buffer*                             g_pBufferResult = NULL;

ID3D11ShaderResourceView*      g_pBuf0SRV = NULL;
ID3D11ShaderResourceView*      g_pBuf1SRV = NULL;
ID3D11UnorderedAccessView*    g_pReslutUAV = NULL;

struct BufType
{
	int i;
	float f;
#ifdef TEST_DOUBLE
	double d;
#endif // TEST_DOUBLE

};

BufType g_vBuf0[NUMELEMENTS];
BufType g_vBUf1[NUMELEMENTS];

int __cdecl main()
{
#if defined (DEBUG)||defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // DEBUG


		printf("Create Device......");
		if (FAILED(CreateComputeDevice(&g_pDevice, &g_pContext, FALSE)))
			return 1;
		printf("done...");

		printf("Create Compute Shader...");
		CreateComputeShader(L"BasicCompute11.hlsl", "CSMain", g_pDevice,&g_pCS);

	return 0;
}