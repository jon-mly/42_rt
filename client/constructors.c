/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:03 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/12/10 16:26:21 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

/*
** Some constructors to emulate a oriented-object programming, that is clearer
** to read.
*/

t_vector	vector(float x, float y, float z)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_vector	vector_points(t_point p1, t_point p2)
{
	t_vector	vector;

	vector.x = p2.x - p1.x;
	vector.y = p2.y - p1.y;
	vector.z = p2.z - p1.z;
	return (vector);
}

t_point		point(float x, float y, float z)
{
	t_point		point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_pixel		pixel(int x, int y)
{
	t_pixel		pixel;

	pixel.x = x;
	pixel.y = y;
	return (pixel);
}

t_color		color(int r, int g, int b, int a)
{
	t_color		color;

	color.r = (unsigned char)r;
	color.g = (unsigned char)g;
	color.b = (unsigned char)b;
	color.a = (unsigned char)a;
	return (color);
}
