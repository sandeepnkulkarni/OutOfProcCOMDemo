// MathServer.cpp : Implementation of CMathServer

#include "pch.h"
#include "MathServer.h"
#include <atlsafe.h>

// CMathServer



STDMETHODIMP CMathServer::ComputePi(DOUBLE* result)
{
	double sum = 0.0;
	int sign = 1;
	for (int i = 0; i < 1024; ++i)
	{
		sum += sign / (2.0 * i + 1.0);
		sign *= -1;
	}

	*result = 4.0 * sum;

	return S_OK;
}

STDMETHODIMP CMathServer::AddIntegers(VARIANT varIntegers, INT* result)
{
	*result = 0;

	if (varIntegers.vt == VT_NULL || varIntegers.vt == VT_EMPTY)
		return E_INVALIDARG;

	if (varIntegers.vt == (VT_ARRAY | VT_I4) && varIntegers.parray != NULL)
	{
		CComSafeArray<INT> vArray(varIntegers.parray);
		int total = 0;

		for (size_t i = 0; i < vArray.GetCount(); i++)
		{
			total += vArray.GetAt(i);
		}

		*result = total;
	}

	return S_OK;
}


STDMETHODIMP CMathServer::get_Floats(VARIANT* pVal)
{
	CComSafeArray<FLOAT> varFloats(m_varFloats.parray);

	V_VT(pVal) = (VT_ARRAY | VT_R4);
	V_ARRAY(pVal) = varFloats.Detach();

	return S_OK;
}


STDMETHODIMP CMathServer::put_Floats(VARIANT newVal)
{
	if (newVal.vt == VT_NULL || newVal.vt == VT_EMPTY)
		return E_INVALIDARG;

	if (newVal.vt == (VT_ARRAY | VT_R4) && newVal.parray != NULL)
	{
		m_varFloats.Clear();
		CComSafeArray<FLOAT> varFloats(newVal.parray);
		
		V_VT(&m_varFloats) = (VT_ARRAY | VT_R4);
		V_ARRAY(&m_varFloats) = varFloats.Detach();
	}

	return S_OK;
}
