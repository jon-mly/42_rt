extern "C" {
#include <rt.h>
#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_object		init_primary_ray(int x, int y, t_camera camera, float aliasing_variation, int horizontal)
{
	t_object		ray;
	t_point			projector_point;
	float			virtual_x;
	float			virtual_y;			

	if (aliasing_variation > 0 && aliasing_variation < 1)
	{
		virtual_x = (float)x + ((horizontal) ? aliasing_variation : 0);
		virtual_y = (float)y + ((!horizontal) ? aliasing_variation : 0);
	}
	else
	{
		virtual_x = (float)x + aliasing_variation;
		virtual_y = (float)y + aliasing_variation;
	}
	projector_point.x = camera.up_left_corner.x + virtual_x * camera.horizontal_vect.x + virtual_y * camera.vertical_vect.x;
	projector_point.y = camera.up_left_corner.y + virtual_x * camera.horizontal_vect.y + virtual_y * camera.vertical_vect.y;
	projector_point.z = camera.up_left_corner.z + virtual_x * camera.horizontal_vect.z + virtual_y * camera.vertical_vect.z;
	ray.direction = vector_pts(camera.spot, projector_point);
	ray.direction = normalize_vec(ray.direction);
	ray.origin = camera.spot;
	ray.refraction = 1;
	ray.reflection = 1;
	ray.transparency = 1;
	ray.intersect = FALSE;
	return (ray);
}

__device__ t_color			primary_ray(t_scene *scene, t_object *obj, t_light *light, t_object ray, int depth, int refraction)
{
	int					object_index;
	int 				closest_object_index;
	float				closest_distance;
	t_color				colorout;
	t_color				refracted_color;
	t_color				reflected_color;
	t_object			intersected_object;

	colorout = BLACK;
	reflected_color = BLACK;
	refracted_color = BLACK;
	closest_object_index = -1;
	object_index = -1;
	while (++object_index < scene->objects_count)
	{
		ray = intersect_obj(ray, obj[object_index]);
		if (ray.intersect && ((closest_object_index != -1 && ray.norm < closest_distance) || closest_object_index == -1) && ray.norm > EPSILON)
		{
			closest_object_index = object_index;
			closest_distance = ray.norm;
		}
	}
	if (closest_object_index != -1)
	{
		ray.norm = closest_distance;
		ray.intersectiion = point_from_vec(ray.origin, ray.direction, closest_distance);
		intersected_object = object_with_local_parameters(obj[closest_object_index], textured_color_if_needed(obj[closest_object_index], ray.intersectiion));
		colorout = get_color_on_inters(ray, intersected_object.index, intersected_object, scene, light, obj);
		if (intersected_object.reflection > 0)
			reflected_color = main_reflected_raytracing(scene, obj, light,
					init_reflected_ray(ray, intersected_object));
		if (intersected_object.transparency > 0)
			refracted_color = main_refracted_raytracing(scene, obj, light,
					init_refracted_ray(ray, intersected_object,
						intersected_object.refraction, intersected_object.transparency));
		colorout = add_color(colorout, add_color(refracted_color, reflected_color));
	}
	colorout = add_color(colorout, direct_light_raytracing(scene, obj, light, ray));
	return (colorout);
}
