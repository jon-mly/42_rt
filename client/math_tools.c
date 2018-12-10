/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:07 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/08/23 14:19:30 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

float		degrees_to_radian(int degrees)
{
	float	radian;

	radian = ((float)degrees * M_PI) / 180.f;
	return (radian);
}

t_vector	vect_rotate_x(t_vector vector, float angle, int inverse)
{
	t_vector	rotated;

	if (!inverse)
	{
		rotated.x = vector.x;
		rotated.y = vector.y * cos(angle) + vector.z * sin(angle);
		rotated.z = -vector.y * sin(angle) + vector.z * cos(angle);
	}
	else
	{
		rotated.x = vector.x;
		rotated.y = cos(angle) * vector.y - sin(angle) * vector.z;
		rotated.z = sin(angle) * vector.y + cos(angle) * vector.z;
	}
	return (rotated);
}

t_vector	vect_rotate_z(t_vector vector, float angle, int inverse)
{
	t_vector	rotated;

	if (!inverse)
	{
		rotated.x = vector.x * cos(angle) + vector.y * sin(angle);
		rotated.y = -vector.x * sin(angle) + vector.y * cos(angle);
		rotated.z = vector.z;
	}
	else
	{
		rotated.x = cos(angle) * vector.x - sin(angle) * vector.y;
		rotated.y = sin(angle) * vector.x + cos(angle) * vector.y;
		rotated.z = vector.z;
	}
	return (rotated);
}

t_vector	vect_rotate_y(t_vector vector, float angle, int inverse)
{
	t_vector	rotated;

	if (!inverse)
	{
		rotated.x = vector.x * cos(angle) - vector.z * sin(angle);
		rotated.y = vector.y;
		rotated.z = vector.x * sin(angle) + vector.z * cos(angle);
	}
	else
	{
		rotated.x = cos(angle) * vector.x + sin(angle) * vector.z;
		rotated.y = vector.y;
		rotated.z = -sin(angle) * vector.x + cos(angle) * vector.z;
	}
	return (rotated);
}

/*
** Solves a quadratic equation but with the aim of returning a distance, which
** has to be a positive value.
** If the value is negative, the equation has no solution.
** Several cases are to be distinguished, in order in the function's body :
** - discriminant < 0 : the ray does not intersect the object
** From this point and for simplication, both x1 and x2 are replaced
** if needed so that x1 <= x2.
** - x1 <= 0 and x2 <= 0 : both intersections are behind the camera,
** so there is no intersection to be represented on screen.
** - x2 > 0 and x1 <= 0 : the camera is inside the object, with one
** point behind the camera, and one in front of it. The one to be
** represented is the one in front of it, so the highest norm
** value.
** - x1 > 0 and x2 > 0 : both intersections are beyond the camera,
** the closest one is to be retained.
*/

float		closest_distance_quadratic(float a, float b, float c)
{
	float		discriminant;
	float		x1;
	float		x2;
	float		buffer;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	x1 = (-b - sqrt(discriminant)) / (2 * a);
	x2 = (-b + sqrt(discriminant)) / (2 * a);
	if (x2 < x1)
	{
		buffer = x2;
		x2 = x1;
		x1 = buffer;
	}
	if (x1 <= 0 && x2 <= 0)
		return (-1);
	else if (x2 > 0 && x1 <= 0)
		return (x2);
	return (x1);
}
