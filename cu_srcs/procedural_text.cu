extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_color			checker_texture_color(t_object object, t_point intersection)
{
	t_color		alternate;
	t_point		adjusted;
	int			x_even;
	int			y_even;
	int			z_even;

	alternate = TRANSPARENT;
	adjusted = scale_vector(intersection, 1.0 / CHECKER_WIDTH);
	x_even = is_texture_even((int)(adjusted.x < -EPSILON) ? adjusted.x - 1 : adjusted.x);
	y_even = is_texture_even((int)(adjusted.y < -EPSILON) ? adjusted.y - 1 : adjusted.y);
	z_even = is_texture_even((int)(adjusted.z < -EPSILON) ? adjusted.z - 1 : adjusted.z);
	if (z_even)
	{
		if ((x_even && y_even)
			|| (!x_even && !y_even))
			return (object.color);
		return (alternate);
	}
	else
	{
		if ((x_even && y_even)
			|| (!x_even && !y_even))
			return (alternate);
		return (object.color);
	}
}

__device__ t_color			circles_color(t_object object, t_point intersection, int horizontal)
{
	t_color		alternate;
	t_point		adjusted;
	int			distance;

	alternate = TRANSPARENT;
	adjusted = scale_vector(intersection, 1.0 / CIRCLES_WIDTH);
	if (horizontal)
		distance = (int)sqrt((adjusted.x * adjusted.x + adjusted.z * adjusted.z));
	else
		distance = (int)sqrt((adjusted.x * adjusted.x + adjusted.y * adjusted.y));
	if (distance % 2 == 0)
		return (object.color);
	return (alternate);
}

__device__ t_color			dots_color(t_object object, t_point intersection, int invert_gradient, int reverse)
{
	float		norm;
	t_color		internal_color;
	t_color		external_color;
	t_point		closest_dot;

	closest_dot = (t_point){round(intersection.x / DOTS_SPREAD) * DOTS_SPREAD,
		round(intersection.y / DOTS_SPREAD) * DOTS_SPREAD,
		round(intersection.z / DOTS_SPREAD) * DOTS_SPREAD};
	if (reverse)
	{
		external_color = object.color;
		internal_color = TRANSPARENT;
	}
	else
	{
		internal_color = object.color;
		external_color = TRANSPARENT;
	}
	norm = pts_norm(intersection, closest_dot);
	if (norm <= DOTS_WIDTH / 2)
		return (internal_color);
	else if (norm <= DOTS_WIDTH)
	{
		if (invert_gradient)
			return (interpolate_color(internal_color, external_color,
				1 - ((norm - DOTS_WIDTH / 2) / (DOTS_WIDTH / 2))));
		else
			return (interpolate_color(internal_color, external_color,
				(norm - DOTS_WIDTH / 2) / (DOTS_WIDTH / 2)));
	}
	return (external_color);
}
