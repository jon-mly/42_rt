extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ int			integer_part(float value)
{
	// return ((int)value);
	if (value >= 0)
		return ((int)value);
	return ((int)value - 1);
	// return ((int)value - (value < 0));
}

__device__ float		fractional_part(float value)
{
	float		integer_part;

	// integer_part = (float)((int)value);
	if (value >= 0)
		integer_part = (float)((int)value);
	else
		integer_part = (float)((int)value - 1);
	// integer_part = (float)((int)value - (value < 0));
	return (value - integer_part);
}
