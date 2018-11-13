extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_color			ambiant_color(t_scene scene, t_object object)
{
	t_color		ambiant_color;
	float		factor;

	factor = scene.power * object.diffuse;
	ambiant_color.r = factor * (object.color.r * scene.theme.r / 255.0);
	ambiant_color.g = factor * (object.color.g * scene.theme.g / 255.0);
	ambiant_color.b = factor * (object.color.b * scene.theme.b / 255.0);
	ambiant_color.a = 0;
	return (ambiant_color);
}

__device__ int				hiit_test(t_object clt_obj, t_object obj, t_object l_ray, float norm)
{
	if (!(l_ray.intersect && l_ray.norm > EPSILON))
		return (0);
	if (clt_obj.index == obj.index)
		return (l_ray.norm < norm - 0.1);
	return (l_ray.norm < norm);
}

__device__ t_color			filter_light_through_object(t_color initial_color, t_object object)
{
	t_color		final_color;
	float		transparency;

	transparency = fmax(object.transparency, (float)((float)object.color.a / 255.0));
	final_color = fade_color(initial_color, transparency);
	final_color.r = final_color.r * object.color.r / 255.0;
	final_color.g = final_color.g * object.color.g / 255.0;
	final_color.b = final_color.b * object.color.b / 255.0;
	return (final_color);
}

__device__ t_object		light_ray_from_shadow_ray(t_object shadow_ray, t_light light)
{
	t_object	light_ray;

	light_ray = shadow_ray;
	light_ray.direction = scale_vector(shadow_ray.direction, -1);
	light_ray.origin = (light.typpe == AMBIANT) ? shadow_ray.origin : light.posiition;
	return (light_ray);
}

__device__ t_color			diffuse_light_for_intersection(t_object light_ray, t_object ray, t_object object, t_light light)
{
	if (light.typpe == AMBIANT)
		return (ambiant_light_for_intersection(light_ray, ray, object, light));
	else if (light.typpe == PROJECTOR)
		return (projector_light_for_intersection(light_ray, ray, object, light));

	return (omni_light_for_intersection(light_ray, ray, object, light));
}
