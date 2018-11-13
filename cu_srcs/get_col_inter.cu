extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_color			get_color_on_inters(t_object ray, int closest_object_index, t_object intersected_object, t_scene *scene, t_light *light, t_object *obj)
{
	t_object	light_ray;
	t_object	shadow_ray;
	int			light_index;
	int			object_index;
	float		norm;
	t_color		coloration;
	t_object	object_inbetween;
	int 		light_goes_through;

	light_index = -1;
	coloration = ambiant_color(*scene, intersected_object);
	while (++light_index < scene->lights_count)
	{
		light_goes_through = 1;
		shadow_ray = get_shadow_ray(light[light_index], ray, intersected_object);
		norm = shadow_ray.norm;
		object_index = -1;
		while (++object_index < scene->objects_count && light_goes_through)
		{
			shadow_ray = intersect_obj(shadow_ray, obj[object_index]);
			if (shadow_ray.intersect && ((light[light_index].typpe == AMBIANT && shadow_ray.norm > EPSILON)
				|| (light[light_index].typpe != AMBIANT && hiit_test(intersected_object, obj[object_index], shadow_ray, norm))))
			{
				shadow_ray.intersectiion = point_from_vec(shadow_ray.origin, shadow_ray.direction, shadow_ray.norm);
				object_inbetween = object_with_local_parameters(obj[object_index], textured_color_if_needed(obj[object_index], shadow_ray.intersectiion));
				shadow_ray.color = filter_light_through_object(shadow_ray.color, object_inbetween);
			}
			light_goes_through = (!(colors_are_equals(shadow_ray.color, BLACK)));
		}
		if (light_goes_through)
		{
			light_ray = light_ray_from_shadow_ray(shadow_ray, light[light_index]);
			coloration = add_color(coloration, diffuse_light_for_intersection(light_ray, ray, intersected_object, light[light_index]));
			coloration = add_color(coloration, specular_light_for_intersection(light_ray, ray, intersected_object, light[light_index]));
		}
	}
	return (coloration);
}

__device__ t_object		get_shadow_ray(t_light light, t_object ray, t_object object)
{
	t_object		shadow_ray;
	t_vector		direction;

	if (light.typpe == AMBIANT)
		shadow_ray.direction = scale_vector(light.direction, -1);
	else
	{
		direction = vector_pts(ray.intersectiion, light.posiition);
		shadow_ray.norm = vec_norm(direction);
		shadow_ray.direction = normalize_vec(direction);
	}
	shadow_ray.origin = point_from_vec(ray.intersectiion, shadow_ray.direction, EPSILON);
	shadow_ray.intersect = FALSE;
	shadow_ray.color = light.color;
	return (shadow_ray);
}
