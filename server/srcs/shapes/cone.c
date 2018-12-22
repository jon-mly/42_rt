/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:14 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/12/21 10:18:35 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector		rotate_cone_angles(t_object cone, t_vector vect,
			int reverse)
{
	if (!reverse)
	{
		vect = vect_rotate_y(vect, cone.y_angle, reverse);
		vect = vect_rotate_x(vect, cone.x_angle, reverse);
	}
	else
	{
		vect = vect_rotate_x(vect, cone.x_angle, reverse);
		vect = vect_rotate_y(vect, cone.y_angle, reverse);
	}
	return (vect);
}

/*
** Returns true if the origin of the light ray is inside the cone,
** meaning that only the inner surface is to be enlighted.
*/

static int		revert_cone_normal(t_object ray, t_object cone)
{
	t_vector	light_to_center;
	float		border;
	float		light_distance;

	light_to_center = vector_points(cone.center, ray.origin);
	light_to_center = rotate_cone_angles(cone, light_to_center, 0);
	border = pow(light_to_center.z, 2) * pow(tan(cone.angle), 2);
	light_distance = pow(light_to_center.x, 2) + pow(light_to_center.y, 2);
	return (light_distance < border);
}

/*
** Calculate the norm of the ray from the origin of it to the intersection
** with the cylinder given in parameter.
** Returns the ray with "intersect" and "norm" values set up
*/

t_object		cone_intersection(t_object ray, t_object cone,
		t_vector distance)
{
	t_vector	ray_dir;
	float		a;
	float		b;
	float		c;
	float		k;

	distance = vector_points(cone.center, ray.origin);
	ray_dir = rotate_cone_angles(cone, ray.direction, 0);
	distance = rotate_cone_angles(cone, distance, 0);
	k = -1 - pow(tan(cone.angle), 2);
	a = pow(vector_norm(ray_dir), 2) + k * pow(ray_dir.z, 2);
	b = 2 * (dot_product(distance, ray_dir) + k * ray_dir.z * distance.z);
	c = pow(vector_norm(distance), 2) + k * pow(distance.z, 2);
	ray.norm = closest_distance_quadratic(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}

t_vector		cone_normal(t_object ray, t_object cone)
{
	t_vector	distance;
	float		normal_dist;
	t_point		normal_point;
	t_point		normal_point_2;
	t_vector	normal;

	distance = vector_points(cone.center, ray.intersectiion);
	distance = rotate_cone_angles(cone, distance, 0);
	normal_dist = (cos(cone.angle) + tan(cone.angle) * sin(cone.angle)) *
		vector_norm(distance);
	normal_point = (t_point){0, 0, normal_dist};
	normal_point_2 = (t_point){0, 0, -normal_dist};
	if (points_norm(normal_point, distance) > points_norm(normal_point_2,
				distance))
		normal_point = normal_point_2;
	if (revert_cone_normal(ray, cone))
		normal = vector_points(distance, normal_point);
	else
		normal = vector_points(normal_point, distance);
	normal = rotate_cone_angles(cone, normal, 1);
	return (normalize_vector(normal));
}
