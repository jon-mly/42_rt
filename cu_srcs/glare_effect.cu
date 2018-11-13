extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_color			direct_light_raytracing(t_scene *scene, t_object *obj, t_light *light, t_object ray)
{
	t_color		glare_color;
	t_light		current_light;
	t_object	associated_plane;
	float		distance_from_origin;
	int			light_index;

	light_index = -1;
	glare_color = BLACK;
	while (++light_index < scene->lights_count)
	{
		current_light = light[light_index];
		if (current_light.typpe != AMBIANT)
			continue;		
		associated_plane = light_plane(ray, current_light);
		ray = intersect_obj(ray, associated_plane);
		if (ray.intersect)
		{
			distance_from_origin = pts_norm(ray.intersectiion, current_light.posiition);
			if (distance_from_origin <= current_light.power / 10)
				glare_color = add_color(glare_color,
					glare_color_from_distance(distance_from_origin, current_light));
		}
	}
	return (glare_color);
}

__device__ t_object		light_plane(t_object ray, t_light light)
{
	t_object	plane;

	// plane = (t_object){
	// 	.point = light.posiition,
	// 	.normal = scale_vector(ray.direction, -1)
	// };
	plane.typpe = PLANE;
	plane.point = light.posiition;
	plane.normal = scale_vector(ray.direction, -1);
	return (plane);
}

__device__ t_color			glare_color_from_distance(float distance, t_light light)
{
	float		intensity;

	intensity = pow((light.power / 10 - distance) / (light.power / 10), 4);
	return (fade_color(light.color, intensity));
}
