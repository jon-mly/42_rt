extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ float		closest_dist_quad(float a, float b, float c)
{
	float		discriminant;
	float		x1;
	float		x2;
	float 		buffer;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	x1 = (-b - sqrt(discriminant)) / (2 * a);
	x2 = (-b + sqrt(discriminant)) / (2 * a);
	if (x2 < x1)
	{
		buffer = x2;
		x2 = x1;
		x1 = buffer;
	}
	if (x1 <= 0 && x2 <= 0)
		return (-1);
	else if (x2 > 0 && x1 <= 0)
		return (x2);
	return (x1);
}

__device__ int			is_texture_even(int value)
{
	if (value >= 0)
		return (value % 2 == 0);
	else
		return ((value) % 2 == 0);
}

__device__ t_color		interpolate_color(t_color c1, t_color c2, float ratio)
{
	t_color		result;

	result.r = fminf(fmaxf(c1.r + (c2.r - c1.r) * ratio, 0), 255);
	result.g = fminf(fmaxf(c1.g + (c2.g - c1.g) * ratio, 0), 255);
	result.b = fminf(fmaxf(c1.b + (c2.b - c1.b) * ratio, 0), 255);
	result.a = fminf(fmaxf(c1.a + (c2.a - c1.a) * ratio, 0), 255);
	return (result);
}

__device__ float		bounded_color_value(float color_value, float min_value, float max_value)
{
	if (color_value < min_value)
		return (min_value);
	else if (color_value > max_value)
		return (max_value);
	return (color_value);
}

__device__ float		farest_distance_quadratic(float a, float b, float c)
{
	float		discriminant;
	float		x1;
	float		x2;
	float 		buffer;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	x1 = (-b - sqrt(discriminant)) / (2 * a);
	x2 = (-b + sqrt(discriminant)) / (2 * a);
	if (x2 < x1)
	{
		buffer = x2;
		x2 = x1;
		x1 = buffer;
	}
	if (x1 <= 0 && x2 <= 0)
		return (-1);
	else if (x2 > 0 && x1 <= 0)
		return (x2);
	return (x2);
}
