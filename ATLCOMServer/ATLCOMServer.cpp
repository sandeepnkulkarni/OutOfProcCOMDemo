// ATLCOMServer.cpp : Implementation of WinMain


#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "ATLCOMServer_i.h"
#include "xdlldata.h"


using namespace ATL;


class CATLCOMServerModule : public ATL::CAtlExeModuleT< CATLCOMServerModule >
{
public:
	DECLARE_LIBID(LIBID_ATLCOMServerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLCOMSERVER, "{68ca1398-e73d-4626-8035-de60dcf49799}")
};

CATLCOMServerModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/,
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}

