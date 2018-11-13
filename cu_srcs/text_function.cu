extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_object		object_with_local_parameters(t_object object, t_color local_color)
{
	t_object	local_object;

	local_object = object;
	local_object.color = local_color;
	local_object.transparency = fmaxf(object.transparency, (float)(local_color.a / 255.0));
	local_object.reflection = object.reflection;
	return (local_object);
}

__device__ t_color			textured_color_if_needed(t_object object, t_point intersection)
{
	if (object.texture_algo == PROCEDURAL)
		return (procedural_color(object, intersection));
	else if (object.texture_algo == PERLIN_ALGO)
		return (perlin_algo_texture_color(object, intersection));
	return (object.color);
}

__device__ t_color			procedural_color(t_object object, t_point intersection)
{
	if (object.texture_type == CHECKER)
		return (checker_texture_color(object, intersection));
	else if (object.texture_type == HORIZONTAL_CIRCLE || object.texture_type == VERTICAL_CIRCLE)
		return (circles_color(object, intersection, object.texture_type == VERTICAL_CIRCLE));
	else if (object.texture_type == DOTS || object.texture_type == DOTS_CROWN
		|| object.texture_type == DOTS_REVERTED || object.texture_type == DOTS_REVERTED_CROWN)
		return (dots_color(object, intersection,
			object.texture_type == DOTS_CROWN || object.texture_type == DOTS_REVERTED_CROWN,
			object.texture_type == DOTS_REVERTED || object.texture_type == DOTS_REVERTED_CROWN));
	return (object.color);
}

__device__ t_color			perlin_algo_texture_color(t_object object, t_point intersection)
{
	if (object.texture_type == PERLIN)
		return (perlin_color(object, intersection));
	else if (object.texture_type == WOOD)
		return (wood_color(object, intersection));
	else if (object.texture_type == MARBLE)
		return (marble_color(object, intersection));
	return (TRANSPARENT);
}
