#include "Framework.h"
#include <type_traits>
#include <cstdio>

const double InputValues[] = 
{
	0.85,
	1.09,
	1.205,
	1.286,
	1.41,
	1.544,
	1.674,
	1.845,
	1.95,
	2.065,
	2.18,
	2.3,
	2.38,
	2.477,
	2.5,
	2.64,
	2.67,
	2.69,
	2.81,
	2.82,
	2.94,
	3.02,
	3.29,
	3.75,
	3.9,
	4.16,
	4.49,
	4.7,
	4.85,
	5.05,
	5.39,
	5.88,
	6,
	6.4,
	6.86,
	7.28,
	7.46,
	8.3,
	8.34,
	8.88,
	9.6,
	9.68,
	10.34,
	10.59,
	10.65,
	10.8,
	11.4,
	11.8,
	12.23,
	12.62,
	12.77,
	13,
	13.35,
	13.47,
	14.47,
	14.64,
	15.8,
	17.8,
	19.2,
	21.92
};

const double OutputValues[] =
{
	0,
	0.23,
	0.34,
	0.45,
	0.58,
	0.71,
	0.83,
	1,
	1.11,
	1.22,
	1.33,
	1.44,
	1.52,
	1.61,
	1.63,
	1.78,
	1.79,
	1.82,
	1.93,
	1.93,
	2.03,
	2.12,
	2.35,
	2.74,
	2.89,
	3.1,
	3.42,
	3.62,
	3.74,
	3.92,
	4.24,
	4.7,
	4.81,
	5.19,
	5.61,
	6,
	6.16,
	6.93,
	6.95,
	7.47,
	8.1,
	8.14,
	8.27,
	8.43,
	8.5,
	8.68,
	9.2,
	9.54,
	9.95,
	10.27,
	10.45,
	10.65,
	10.94,
	11.07,
	11.93,
	12.1,
	13.1,
	14.8,
	16,
	18.25,
};

template <typename T, int N> const char(&__countof(T(&)[N]))[N];
#define countof(arr) static_cast<int>(sizeof(__countof(arr)))

template <typename T>
T Lerp(T a, T b, T amount)
{
	static_assert(std::is_floating_point<T>::value, "");
	return a + (b - a) * amount;
}

double InputToOutputPower(double inputWattage)
{
	if (inputWattage < InputValues[0])
		return 0;

	for (int i = 0; i < countof(InputValues) - 1; i++)
	{
		if (inputWattage < InputValues[i + 1])
		{
			double pos = (inputWattage - InputValues[i]) / (InputValues[i + 1] - InputValues[i]);
			return Lerp(OutputValues[i], OutputValues[i + 1], pos);
		}
	}

	// extended curve fit
	return -1.446332 + 0.9765686 * inputWattage - 0.003556437 * inputWattage * inputWattage;
}


bool ReadRecording(const char* fp, Recording* result, int* count)
{
	FILE* f = fopen(fp, "rb");
	if (!f)
		return false;

	fseek(f, 0x31, SEEK_SET);

	int counter = 0;
	while (!feof(f))
	{
		Recording item;
		fread(&item.m_time, sizeof(item.m_time), 1, f);
		fread(&item.m_power, sizeof(item.m_power), 1, f);

		if (counter == 0 && item.m_time != 0)
		{
			fclose(f);
			return false;
		}

		if (result)
		{
			result[counter] = item;
		}
		counter++;
	}

	if (count)
	{
		*count = counter;
	}

	fclose(f);
	return true;
}