#pragma once

#ifdef DCDC_EXPORTS
#define DCDC_API __declspec(dllexport)
#else
#define DCDC_API __declspec(dllimport)
#endif

struct Recording
{
	double m_time;
	double m_power;
};

extern "C"
{
	DCDC_API double InputToOutputPower(double inputWattage);

	DCDC_API bool ReadRecording(const char* fp, Recording* result, int* count);
}
