/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:18 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/12/21 10:18:41 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Ref is supposed to be (0,0,1) in the new referential.
** - lat : lattitude of the reference, Oz rotation
** - lon : longitude of the reference, Oy rotation.
** - projected_ref : copy of ref with a coordinate nulled (projection on a
** given axis)
** - unit : unit vector, either (1,0,0)
*/

t_vector		rotate_cylinder_angles(t_object cylinder, t_vector vect,
			int reverse)
{
	if (!reverse)
	{
		vect = vect_rotate_y(vect, cylinder.y_angle, reverse);
		vect = vect_rotate_x(vect, cylinder.x_angle, reverse);
	}
	else
	{
		vect = vect_rotate_x(vect, cylinder.x_angle, reverse);
		vect = vect_rotate_y(vect, cylinder.y_angle, reverse);
	}
	return (vect);
}

static int		revert_cylinder_normal(t_object ray, t_object cylinder)
{
	t_vector	light_to_center;
	float		border;
	float		light_distance;

	light_to_center = vector_points(cylinder.point, ray.origin);
	light_to_center = rotate_cylinder_angles(cylinder, light_to_center, 0);
	border = pow(cylinder.radius, 2);
	light_distance = pow(light_to_center.x, 2) + pow(light_to_center.y, 2);
	return (light_distance < border);
}

/*
** Calculate the norm of the ray from the origin of it to the intersection
** with the cylinder given in parameter.
** Returns the ray with "intersect" and "norm" values set up
*/

t_object		cylinder_intersection(t_object ray, t_object cylinder)
{
	t_vector	distance;
	t_vector	ray_dir;
	float		a;
	float		b;
	float		c;

	distance = vector_points(cylinder.point, ray.origin);
	ray_dir = rotate_cylinder_angles(cylinder, ray.direction, 0);
	distance = rotate_cylinder_angles(cylinder, distance, 0);
	a = pow(ray_dir.x, 2.) + pow(ray_dir.y, 2.);
	b = 2 * (distance.x * ray_dir.x + distance.y * ray_dir.y);
	c = pow(distance.x, 2.) + pow(distance.y, 2.) - pow(cylinder.radius, 2.);
	ray.norm = closest_distance_quadratic(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}

t_vector		cylinder_normal(t_object ray, t_object cylinder)
{
	t_vector	distance;
	t_point		normal_point;
	t_vector	normal;

	distance = vector_points(cylinder.point, ray.intersectiion);
	distance = rotate_cylinder_angles(cylinder, distance, 0);
	normal_point = (t_point){0, 0, distance.z};
	if (revert_cylinder_normal(ray, cylinder))
		normal = vector_points(distance, normal_point);
	else
		normal = vector_points(normal_point, distance);
	normal = rotate_cylinder_angles(cylinder, normal, 1);
	return (normalize_vector(normal));
}
