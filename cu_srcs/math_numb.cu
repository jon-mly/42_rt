extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ float		vec_norm(t_vector vec)
{
	float		norm;

	norm = sqrt((float)(pow((float)vec.x, (float)2) + pow((float)vec.y, (float)2) + pow((float)vec.z, (float)2)));
	return (norm);
}

__device__ float		dot_prod(t_vector vect_1, t_vector vect_2)
{
	float		product;

	product = (vect_1.x * vect_2.x) +
				(vect_1.y * vect_2.y) +
				(vect_1.z * vect_2.z);
	return (product);
}

__device__ t_vector		cross_prod(t_vector vect_1, t_vector vect_2)
{
	t_vector	cross;

	cross.x = vect_1.y * vect_2.z - vect_1.z * vect_2.y;
	cross.y = vect_1.z * vect_2.x - vect_1.x * vect_2.z;
	cross.z = vect_1.x * vect_2.y - vect_1.y * vect_2.x;
	return (cross);
}

__device__ float		linear_interpolation(float a, float b, float ratio)
{
	return (a + (b - a) * ratio);
}
