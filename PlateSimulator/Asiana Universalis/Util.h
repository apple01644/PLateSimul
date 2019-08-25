#pragma once

#ifndef _UTILCLASS_H_
#define _UTILCLASS_H_


#include <WindowsNumerics.h>

using namespace Windows::Foundation::Numerics;

class Util {
public:
	float3 HSV2RGB(double, double, double);
	double PP2DIR(double, double);
};

#endif