// MathServer.cpp : Implementation of CMathServer

#include "pch.h"
#include "MathServer.h"


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
