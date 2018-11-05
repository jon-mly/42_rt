/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:54 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/11/05 13:42:43 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_object			init_ray(int x, int y, t_camera camera)
{
	t_object		ray;
	t_point			projector_point;

	projector_point.x = camera.up_left_corner.x + (double)x
		* camera.horizontal_vect.x + (double)y * camera.vertical_vect.x;
	projector_point.y = camera.up_left_corner.y + (double)x
		* camera.horizontal_vect.y + (double)y * camera.vertical_vect.y;
	projector_point.z = camera.up_left_corner.z + (double)x
		* camera.horizontal_vect.z + (double)y * camera.vertical_vect.z;
	ray.direction = vector_points(camera.spot, projector_point);
	ray.direction = normalize_vector(ray.direction);
	ray.origin = camera.spot;
	ray.intersect = FALSE;
	return (ray);
}

static	void		pixel_raytracing2(t_object *ray, float *closest_distance)
{
	ray->norm = *closest_distance;
	ray->intersectiion.x = ray->origin.x + ray->direction.x * *closest_distance;
	ray->intersectiion.y = ray->origin.y + ray->direction.y * *closest_distance;
	ray->intersectiion.z = ray->origin.z + ray->direction.z * *closest_distance;
}

void				pixel_raytracing(int x, int y, t_env *env)
{
	t_object		ray;
	int				object_index;
	t_object		*clt_obj;
	float			clt_dist;

	ray = init_ray(x, y, env->camera);
	clt_obj = NULL;
	object_index = -1;
	while (++object_index < env->scene.objects_count)
	{
		ray = intersect_object(ray, env->scene.objects[object_index]);
		if (ray.intersect && ((clt_obj != NULL && ray.norm < clt_dist)
					|| clt_obj == NULL) && ray.norm > 0)
		{
			clt_obj = &env->scene.objects[object_index];
			clt_dist = ray.norm;
		}
	}
	if (clt_obj != NULL)
	{
		pixel_raytracing2(&ray, &clt_dist);
		fill_pixel(env, x, y, get_color_on_intersection(ray, clt_obj, env));
	}
	else
		fill_pixel(env, x, y, color(0, 0, 0, 0));
}
