extern "C" {
#include <rt.h>
#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_object		init_reflected_ray(t_object original_ray, t_object intersected_object)
{
	t_object	ray;

	ray.direction = reflected_vector(original_ray.direction, shape_norml(original_ray, intersected_object));
	ray.direction = normalize_vec(ray.direction);
	ray.origin = point_from_vec(original_ray.intersectiion, ray.direction, EPSILON);
	ray.intersect = FALSE;
	ray.reflection = intersected_object.reflection * original_ray.reflection * (1 - intersected_object.transparency);
	ray.refraction = intersected_object.refraction;
	ray.transparency = intersected_object.transparency;
	return (ray);
}

__device__ t_color			main_reflected_raytracing(t_scene *scene, t_object *obj, t_light *light, t_object ray)
{
	int					object_index;
	int 				closest_object_index;
	float				closest_distance;
	t_color				added_color;
	int					iter_count;
	t_color				colorout;
	int					max_iterations;
	t_object			intersected_object;

	iter_count = -1;
	max_iterations = MAX_DEPTH;
	colorout = BLACK;
	while (++iter_count < max_iterations) {
		added_color = BLACK;
		closest_object_index = -1;
		object_index = -1;
		while (++object_index < scene->objects_count)
		{
			ray = intersect_obj(ray, obj[object_index]);
			if (ray.intersect && ((closest_object_index != -1 && ray.norm < closest_distance)
						|| closest_object_index == -1) && ray.norm > EPSILON)
			{
				closest_object_index = object_index;
				closest_distance = ray.norm;
			}
		}
		if (closest_object_index != -1)
		{
			ray.norm = closest_distance;
			ray.intersectiion = point_from_vec(ray.origin, ray.direction, closest_distance);
			intersected_object = object_with_local_parameters(obj[closest_object_index],
					textured_color_if_needed(obj[closest_object_index], ray.intersectiion));
			added_color = get_color_on_inters(ray, intersected_object.index, intersected_object, scene, light, obj);
			added_color = fade_color(added_color, ray.reflection);
			if (intersected_object.transparency > 0)
				added_color = add_color(added_color, ponctual_refracted_raytracing(scene, obj, light,
							init_refracted_ray(ray, intersected_object,
								intersected_object.refraction, intersected_object.transparency)));
		}
		colorout = add_color(colorout, added_color);
		if (closest_object_index == -1 || intersected_object.reflection == 0)
			return (colorout);
		ray = init_reflected_ray(ray, intersected_object);
	}
	return (colorout);
}

__device__ t_color			ponctual_reflected_raytracing(t_scene *scene, t_object *obj, t_light *light, t_object ray)
{
	int					object_index;
	int 				closest_object_index;
	float				closest_distance;
	t_color				added_color;
	int					iter_count;
	t_color				colorout;
	int					max_iterations;
	t_object			intersected_object;

	iter_count = -1;
	max_iterations = 2;
	colorout = BLACK;
	while (++iter_count < max_iterations) {
		added_color = BLACK;
		closest_object_index = -1;
		object_index = -1;
		while (++object_index < scene->objects_count)
		{
			ray = intersect_obj(ray, obj[object_index]);
			if (ray.intersect && ((closest_object_index != -1 && ray.norm < closest_distance)
						|| closest_object_index == -1) && ray.norm > EPSILON)
			{
				closest_object_index = object_index;
				closest_distance = ray.norm;
			}
		}
		if (closest_object_index != -1)
		{
			ray.norm = closest_distance;
			ray.intersectiion = point_from_vec(ray.origin, ray.direction, closest_distance);
			intersected_object = object_with_local_parameters(obj[closest_object_index],
					textured_color_if_needed(obj[closest_object_index], ray.intersectiion));
			added_color = get_color_on_inters(ray, intersected_object.index, intersected_object, scene, light, obj);
			added_color = fade_color(added_color, ray.reflection);
		}
		colorout = add_color(colorout, added_color);
		if (closest_object_index == -1 || intersected_object.reflection == 0)
			return (colorout);
		ray = init_reflected_ray(ray, intersected_object);
	}
	return (colorout);
}
