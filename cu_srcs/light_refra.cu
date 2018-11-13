extern "C" {
#include <rt.h>
#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_object		init_refracted_ray(t_object original_ray, t_object intersected_object, float next_refraction, float next_transparency)
{
	t_object		ray;

	ray.direction = refracted_vector(original_ray, intersected_object, next_refraction);
	ray.origin = point_from_vec(original_ray.intersectiion, ray.direction, EPSILON);
	ray.intersect = FALSE;
	ray.transparency = next_transparency;
	ray.refraction = next_refraction;
	ray.reflection = intersected_object.reflection * original_ray.reflection;
	return (ray);
}

__device__ t_color			main_refracted_raytracing(t_scene *scene, t_object *obj, t_light *light, t_object ray)
{
	int					object_index;
	int 				closest_object_index;
	float				closest_distance;
	t_color				added_color;
	t_color				colorout;
	int					iter_count;
	int					max_iterations;
	int					inside_object;
	int					current_object_id;
	t_object			intersected_object;

	iter_count = -1;
	max_iterations = MAX_DEPTH;
	colorout = BLACK;
	current_object_id = -1;
	inside_object = FALSE;
	while (++iter_count < max_iterations * 2) {
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
			if (inside_object && current_object_id == obj[closest_object_index].id)
				inside_object = FALSE;
			else if (!inside_object)
			{
				current_object_id = obj[closest_object_index].id;
				inside_object = TRUE;
			}
			ray.norm = closest_distance;
			ray.intersectiion = point_from_vec(ray.origin, ray.direction, closest_distance);
			intersected_object = object_with_local_parameters(obj[closest_object_index],
					textured_color_if_needed(obj[closest_object_index], ray.intersectiion));
			added_color = get_color_on_inters(ray, intersected_object.index, intersected_object, scene, light, obj);
			added_color = fade_color(added_color, ray.transparency);
			if (intersected_object.reflection > 0)
				added_color = add_color(added_color, ponctual_reflected_raytracing(scene, obj, light,
							init_reflected_ray(ray, intersected_object)));
			colorout = add_color(colorout, added_color);
		}
		if (closest_object_index == -1 || intersected_object.transparency == 0)
			return (colorout);
		if (!inside_object)
			ray = init_refracted_ray(ray, intersected_object,
					1, ray.transparency);
		else
			ray = init_refracted_ray(ray, intersected_object,
					intersected_object.refraction, intersected_object.transparency);


	}
	return (colorout);
}

__device__ t_color			ponctual_refracted_raytracing(t_scene *scene, t_object *obj, t_light *light, t_object ray)
{
	int					object_index;
	int 				closest_object_index;
	float				closest_distance;
	t_color				added_color;
	t_color				colorout;
	int					iter_count;
	int					max_iterations;
	int					inside_object;
	int					current_object_id;
	t_object			intersected_object;

	iter_count = -1;
	max_iterations = MAX_DEPTH;
	colorout = BLACK;
	current_object_id = -1;
	inside_object = FALSE;
	while (++iter_count < max_iterations * 2) {
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
			if (inside_object && current_object_id == obj[closest_object_index].id)
				inside_object = FALSE;
			else if (!inside_object)
			{
				current_object_id = obj[closest_object_index].id;
				inside_object = TRUE;
			}
			ray.norm = closest_distance;
			ray.intersectiion = point_from_vec(ray.origin, ray.direction, closest_distance);
			intersected_object = object_with_local_parameters(obj[closest_object_index],
					textured_color_if_needed(obj[closest_object_index], ray.intersectiion));
			added_color = get_color_on_inters(ray, intersected_object.index, intersected_object, scene, light, obj);
			added_color = fade_color(added_color, ray.transparency);
			colorout = add_color(colorout, added_color);
		}
		if (closest_object_index == -1 || intersected_object.transparency == 0)
			return (colorout);
		if (!inside_object)
			ray = init_refracted_ray(ray, intersected_object,
					1, ray.transparency);
		else
			ray = init_refracted_ray(ray, intersected_object,
					intersected_object.refraction, intersected_object.transparency);


	}
	return (colorout);
}
