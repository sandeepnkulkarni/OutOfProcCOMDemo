// NativeMathClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <atlbase.h>
#include <iostream>
#include <iomanip>

#include "..\ATLCOMServer\ATLCOMServer_i.h"
#include "..\ATLCOMServer\ATLCOMServer_i.c"

int main()
{
	::SetConsoleOutputCP(CP_UTF8);

	HRESULT hr;
	hr = ::CoInitializeEx(0, COINITBASE_MULTITHREADED);
	if (FAILED(hr))
	{
		std::cout << "CoInitializeEx failure: " << std::hex << std::showbase << hr << std::endl;
		return EXIT_FAILURE;
	}

	CComPtr<IMathServer> mathServer;
	hr = ::CoCreateInstance(CLSID_MathServer, nullptr, CLSCTX_LOCAL_SERVER, __uuidof(IMathServer), (void **)&mathServer);
	if (FAILED(hr))
	{
		std::cout << "CoCreateInstance failure: " << std::hex << std::showbase << hr << std::endl;
		return EXIT_FAILURE;
	}

	double pi;
	hr = mathServer->ComputePi(&pi);
	if (FAILED(hr))
	{
		std::cout << "Failure: " << std::hex << std::showbase << hr << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << u8"\u03C0 = " << std::setprecision(16) << pi << std::endl;

	::CoUninitialize();

	return EXIT_SUCCESS;
}
