// MathServer.h : Declaration of the CMathServer

#pragma once
#include "resource.h"       // main symbols



#include "ATLCOMServer_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CMathServer

class ATL_NO_VTABLE CMathServer :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMathServer, &CLSID_MathServer>,
	public IDispatchImpl<IMathServer, &IID_IMathServer, &LIBID_ATLCOMServerLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CMathServer()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_MATHSERVER)

	BEGIN_COM_MAP(CMathServer)
		COM_INTERFACE_ENTRY(IMathServer)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	STDMETHOD(ComputePi)(DOUBLE* result);
};

OBJECT_ENTRY_AUTO(__uuidof(MathServer), CMathServer)
