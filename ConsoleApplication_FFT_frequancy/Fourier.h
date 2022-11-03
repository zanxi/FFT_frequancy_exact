#pragma once

const int NumData = 45000;

class CFourier
{
public:
	double pi;
	unsigned long int fundamental_frequency;
	float *vector;
	CFourier(void);
	~CFourier(void);
	// FFT 1D
	void _FFT(float data[], unsigned long number_of_samples, unsigned int sample_rate, int sign);
};
