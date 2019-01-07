/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:29:44 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/21 10:19:00 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Returns true if the origin of the light ray is inside the sphere,
** meaning that only the inner surface is to be enlighted.
*/

static int		revert_sphere_normal(t_object ray, t_object sphere)
{
	t_vector	distance_vector;

	distance_vector = vector_points(ray.origin, sphere.center);
	return (vector_norm(distance_vector) < sphere.radius);
}

/*
** Calculate the norm of the ray from the origin of it to the intersection
** with the sphere given in parameter.
** Returns the ray with "intersect" and "norm" values set up
*/

t_object		sphere_intersection(t_object ray, t_object sphere)
{
	float		a;
	float		b;
	float		c;
	t_vector	distance;

	distance = vector_points(sphere.center, ray.origin);
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(ray.direction, distance);
	c = dot_product(distance, distance) - pow(sphere.radius, 2);
	ray.norm = closest_distance_quadratic(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}

t_vector		sphere_normal(t_object ray, t_object sphere)
{
	t_vector	normal;

	if (revert_sphere_normal(ray, sphere))
		normal = vector_points(ray.intersectiion, sphere.center);
	else
		normal = vector_points(sphere.center, ray.intersectiion);
	return (normalize_vector(normal));
}
