extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_color			specular_light_for_intersection(t_object light_ray, t_object ray, t_object object, t_light light)
{
	float		distance;
	float		intensity;
	t_vector	incident;
	t_vector	reflected;
	t_color		specular;

	if (light.typpe == PROJECTOR && dot_prod(light_ray.direction, light.direction) < cosf(light.angle))
		return (BLACK);
	incident = scale_vector(light_ray.direction, -1);
	distance = (light.typpe != AMBIANT)
		? pts_norm(ray.intersectiion, light_ray.origin) * (100.0 / light.power)
		: 100.0 * (100.0 / light.power);
		distance = 1;
	reflected = reflected_vector(incident, shape_norml(ray, object));
	intensity = powf(fmaxf(dot_prod(reflected, ray.direction), 0), (int)(object.brillance * 100)) * powf(object.brillance, 2);
	intensity *= (1 - object.transparency);
	if (light.typpe == PROJECTOR)
		intensity *= (1 / (1 - cosf(light.angle))) * dot_prod(light.direction, light_ray.direction) - (cosf(light.angle) / (1 - cosf(light.angle)));
	specular.r = projector_color_coord(intensity, distance, object.color.r, light_ray.color.r);
	specular.g = projector_color_coord(intensity, distance, object.color.g, light_ray.color.g);
	specular.b = projector_color_coord(intensity, distance, object.color.b, light_ray.color.b);
	specular.a = 0;
	return (specular);
}

__device__ t_color			ambiant_light_for_intersection(t_object light_ray, t_object ray, t_object object, t_light light)
{
	t_color		color;
	float		distance;
	float		cosinus;

	cosinus = dot_prod(scale_vector(light_ray.direction, -1), shape_norml(ray, object)) * object.diffuse * (1 - object.transparency);
	if (cosinus <= 0)
		return (BLACK);
	distance = 100.0 * (100.0 / light.power);
	color.r = omni_color_coord(-cosinus, distance, object.color.r, light_ray.color.r);
	color.g = omni_color_coord(-cosinus, distance, object.color.g, light_ray.color.g);
	color.b = omni_color_coord(-cosinus, distance, object.color.b, light_ray.color.b);
	color.a = 0;
	return (color);
}

__device__ t_color			projector_light_for_intersection(t_object light_ray, t_object ray, t_object object, t_light light)
{
	t_vector	normal;
	float		cosinus;
	float		distance;
	float 		intensity;
	t_color		color;

	if (dot_prod(light.direction, light_ray.direction) < cosf(light.angle))
		return (BLACK);
	light_ray.intersectiion = ray.intersectiion;
	normal = shape_norml(ray, object);
	distance = pts_norm(ray.intersectiion, light_ray.origin) * (100.0 / light.power);
	cosinus = dot_prod(light.direction, light_ray.direction);
	intensity = (1 / (1 - cosf(light.angle))) * cosinus - (cosf(light.angle) / (1 - cosf(light.angle)));
	intensity *= object.diffuse * (1 - object.transparency);
	cosinus = dot_prod(light_ray.direction, normal);
	if (cosinus >= 0)
		return (BLACK);
	intensity = -cosinus * intensity;
	color.r = projector_color_coord(intensity, distance, object.color.r, light_ray.color.r) * object.diffuse;
	color.g = projector_color_coord(intensity, distance, object.color.g, light_ray.color.g) * object.diffuse;
	color.b = projector_color_coord(intensity, distance, object.color.b, light_ray.color.b) * object.diffuse;
	color.a = 0;
	return (color);
}

__device__ t_color			omni_light_for_intersection(t_object light_ray, t_object ray, t_object object, t_light light)
{
	t_vector	normal;
	float		cosinus;
	float		distance;
	t_color		color;

	light_ray.intersectiion = ray.intersectiion;
	normal = shape_norml(ray, object);
	cosinus = dot_prod(light_ray.direction, normal) * object.diffuse * (1 - object.transparency);
	if (cosinus >= 0)
		return (BLACK);
	distance = pts_norm(ray.intersectiion, light_ray.origin) * (100.0 / light.power);
	color.r = omni_color_coord(cosinus, distance, object.color.r, light_ray.color.r) * object.diffuse;
	color.g = omni_color_coord(cosinus, distance, object.color.g, light_ray.color.g) * object.diffuse;
	color.b = omni_color_coord(cosinus, distance, object.color.b, light_ray.color.b) * object.diffuse;
	color.a = 0;
	return (color);
}

__device__ int			projector_color_coord(float intensity, float distance, int obj_color, int light_color)
{
	float		color_value;
	float		distance_factor;
	float		k;

	distance_factor = 0.02 * pow((float)(distance / 1.3), (float)2) + 1;
	k = intensity / distance_factor;
	color_value = ((float)obj_color + (float)light_color) * k;
	color_value = maximize_color_value((int)color_value);
	return ((int)color_value);
}
