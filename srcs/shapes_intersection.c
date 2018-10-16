/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:27:22 by aabelque          #+#    #+#             */
/*   Updated: 2018/08/23 15:39:30 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_object			intersect_object(t_object ray, t_object object)
{
	t_vector	distance;

	if (object.typpe == SPHERE)
		ray = sphere_intersection(ray, object);
	else if (object.typpe == PLANE)
		ray = plane_intersection(ray, object);
	else if (object.typpe == CYLINDER)
		ray = cylinder_intersection(ray, object);
	else if (object.typpe == CONE)
		ray = cone_intersection(ray, object, distance);
	if (ray.intersect)
	{
		ray.intersectiion.x = ray.origin.x + ray.direction.x * ray.norm;
		ray.intersectiion.y = ray.origin.y + ray.direction.y * ray.norm;
		ray.intersectiion.z = ray.origin.z + ray.direction.z * ray.norm;
	}
	return (ray);
}
