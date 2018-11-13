extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_vector		sum_vectors(t_vector vect1, t_vector vect2)
{
	t_vector	sum;

	sum.x = vect1.x + vect2.x;
	sum.y = vect1.y + vect2.y;
	sum.z = vect1.z + vect2.z;
	return (sum);
}

__device__ t_vector		scale_vector(t_vector vect, float scale)
{
	vect.x *= scale;
	vect.y *= scale;
	vect.z *= scale;
	return (vect);
}

__device__ t_vector		rotate_vec_angles(t_object reference, t_vector vect, int reverse)
{
	if (!reverse)
	{
		vect = vec_rotate_y(vect, reference.y_angle, reverse);
		vect = vec_rotate_x(vect, reference.x_angle, reverse);
	}
	else
	{
		vect = vec_rotate_x(vect, reference.x_angle, reverse);
		vect = vec_rotate_y(vect, reference.y_angle, reverse);
	}
	return (vect);
}

__device__ t_vector		vec_rotate_x(t_vector vector, float angle, int inverse)
{
	t_vector	rotated;

	if (!inverse)
	{
		rotated.x = vector.x;
		rotated.y = vector.y * cosf(angle) + vector.z * sinf(angle);
		rotated.z = -vector.y * sinf(angle) + vector.z * cosf(angle);
	}
	else
	{
		rotated.x = vector.x;
		rotated.y = cosf(angle) * vector.y - sinf(angle) * vector.z;
		rotated.z = sinf(angle) * vector.y + cosf(angle) * vector.z;
	}
	return (rotated);
}

__device__ t_vector		vec_rotate_y(t_vector vector, float angle, int inverse)
{
	t_vector	rotated;

	if (!inverse)
	{
		rotated.x = vector.x * cosf(angle) - vector.z * sinf(angle);
		rotated.y = vector.y;
		rotated.z = vector.x * sinf(angle) + vector.z * cosf(angle);
	}
	else
	{
		rotated.x = cosf(angle) * vector.x + sinf(angle) * vector.z;
		rotated.y = vector.y;
		rotated.z = -sinf(angle) * vector.x + cosf(angle) * vector.z;
	}
	return (rotated);
}
