// NativeMathClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <atlbase.h>
#include <atlsafe.h>
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

	CComSafeArray<INT> input(5);
	for (LONG i = input.GetLowerBound(); i <= input.GetUpperBound(); i++)
	{
		input.SetAt(i, (i + 1));
	}

	CComVariant varIntegers;
	V_VT(&varIntegers) = (VT_ARRAY | VT_I4);
	V_ARRAY(&varIntegers) = input.Detach();
	
	int result = 0;
	hr = mathServer->AddIntegers(varIntegers, &result);
	if (FAILED(hr))
	{
		std::cout << "Failure: " << std::hex << std::showbase << hr << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "Integer addition result = " << result << std::endl;

	CComSafeArray<FLOAT> floatInput(3);
	for (LONG i = floatInput.GetLowerBound(); i <= floatInput.GetUpperBound(); i++)
	{
		float val = float(i + 1) + (float(i + 1) * 0.1f);
		floatInput.SetAt(i, val);
	}

	CComVariant varFloats;
	V_VT(&varFloats) = (VT_ARRAY | VT_R4);
	V_ARRAY(&varFloats) = floatInput.Detach();

	hr = mathServer->put_Floats(varFloats);

	std::cout << "put_Floats result = " << hr << std::endl;

	CComVariant varFloatsResult;
	hr = mathServer->get_Floats(&varFloatsResult);

	std::cout << "get_Floats result = " << varFloatsResult.vt << std::endl;

	::CoUninitialize();

	return EXIT_SUCCESS;
}
