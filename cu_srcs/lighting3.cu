extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ int			omni_color_coord(float cosinus, float distance, int obj_color, int light_color)
{
	float	distance_factor;
	float	k;
	float	color_value;

	distance_factor = 0.02 * pow((float)(distance / 1.3), (float)2) + 1;
	k = sqrt(-cosinus) / distance_factor;
	color_value = ((float)obj_color + (float)light_color) * k;
	color_value = maximize_color_value((int)color_value);
	return ((int)color_value);
}
