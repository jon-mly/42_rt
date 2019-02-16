/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:03 by jmlynarc          #+#    #+#             */
/*   Updated: 2019/02/16 17:02:27 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Some constructors to emulate a oriented-object programming, that is clearer
** to read.
*/

t_vector			vector(float x, float y, float z)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_vector			vector_points(t_point p1, t_point p2)
{
	t_vector	vector;

	vector.x = p2.x - p1.x;
	vector.y = p2.y - p1.y;
	vector.z = p2.z - p1.z;
	return (vector);
}

t_point				point(float x, float y, float z)
{
	t_point		point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_color				color(int r, int g, int b, int a)
{
	t_color		color;

	color.r = (unsigned char)r;
	color.g = (unsigned char)g;
	color.b = (unsigned char)b;
	color.a = (unsigned char)a;
	return (color);
}

/*
** Returns an object with arbitrary / default values.
** This is used to avoid random values to be set if some parameters
** are not defined.
*/

t_object			get_template_object(void)
{
	return ((t_object){
		.finite = FALSE, .covered = FALSE, .radius = 1.0,
		.angle = 0, .y_angle = 0, .x_angle = 0,
		.brillance = 0, .reflection = 0, .diffuse = 1.0,
		.transparency = 0.0, .refraction = 1.0, .height = 1.0,
		.width = 1.0, .rho = 1.0, .sigma = 1.0,
		.center = (t_point){0, 0, 0},
		.point = (t_point){0, 0, 0},
		.direction = (t_vector){1, 0, 0},
		.normal = (t_vector){1, 0, 0},
		.first_vect = (t_vector){1, 0, 0},
		.second_vect = (t_vector){0, 1, 0},
		.color = (t_color){200, 200, 200, 1},
		.typpe = SPHERE, .txt_type = NONE,
		.bump_mapping = FLAT
	});
}
