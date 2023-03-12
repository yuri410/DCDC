#pragma once

#ifdef DCDC_EXPORTS
#define DCDC_API __declspec(dllexport)
#else
#define DCDC_API __declspec(dllimport)
#endif

extern "C"
{
	DCDC_API double InputToOutputPower(double inputWattage);
}
