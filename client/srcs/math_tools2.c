/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:16:53 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/21 18:43:57 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_vector		cross_product(t_vector vect_1, t_vector vect_2)
{
	t_vector	product;

	product.x = vect_1.y * vect_2.z - vect_2.y * vect_1.z;
	product.y = vect_1.z * vect_2.x - vect_2.z * vect_1.x;
	product.z = vect_1.x * vect_2.y - vect_2.x * vect_1.y;
	return (product);
}

t_vector		normalize_vector(t_vector vector)
{
	float		norm;

	norm = vector_norm(vector);
	vector.x /= norm;
	vector.y /= norm;
	vector.z /= norm;
	return (vector);
}

float			points_norm(t_point p1, t_point p2)
{
	float		distance;

	distance = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) +
			pow(p2.z - p1.z, 2));
	return (distance);
}

t_vector		point_from_vector(t_point origin,
		t_vector direction, float norm)
{
	t_point		point;

	point.x = origin.x + direction.x * norm;
	point.y = origin.y + direction.y * norm;
	point.z = origin.z + direction.z * norm;
	return (point);
}

t_vector		rotate_vector_angles(t_object reference, t_vector vect,
			int reverse)
{
	if (!reverse)
	{
		vect = vect_rotate_y(vect, reference.y_angle, reverse);
		vect = vect_rotate_x(vect, reference.x_angle, reverse);
	}
	else
	{
		vect = vect_rotate_x(vect, reference.x_angle, reverse);
		vect = vect_rotate_y(vect, reference.y_angle, reverse);
	}
	return (vect);
}
