/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_creation2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 12:00:40 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/21 17:11:16 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** sphere
** required structure
**
** sphere {
** radius [radius]
** center [x] [y] [z]
** color [r] [g] [b]
** }
*/

t_object		add_new_sphere(int fd)
{
	t_object	sphere;

	sphere.typpe = SPHERE;
	sphere.txt_type = NONE;
	sphere.bump_mapping = FLAT;
	sphere.radius = 1;
	sphere.center = point(10, 12, 6);
	sphere.color = color(255, 255, 255, 0);
	sphere = parse_object(fd, &sphere);
	return (sphere);
}

/*
** plane
** required structure
**
** plane {
** normal [x] [y] [z]
** point [x] [y] [z]
** color [r] [g] [b]
** }
*/

t_object		add_new_plane(int fd)
{
	char		**line;
	t_object	plane;

	plane.typpe = PLANE;
	plane.txt_type = NONE;
	plane.bump_mapping = FLAT;
	plane.normal = normalize_vector(vector(0, 1, 0));
	plane.point = point(0, 0, 0);
	plane.color = color(255, 255, 255, 0);
	plane = parse_object(fd, &plane);
	return (plane);
}

/*
** cone
** required structure
**
** cone {
** pi_divider [PI / x . x value expected]
** direction [x] [y] [z]
** center [x] [y] [z]
** color [r] [g] [b]
** }
*/

t_object		add_new_cone(int fd)
{
	t_object	cone;

	cone.typpe = CONE;
	cone.txt_type = NONE;
	cone.bump_mapping = FLAT;
	cone.angle = M_PI / 6;
	cone.direction = normalize_vector(vector(0, 0, 1));
	cone.center = point(0, 0, 0);
	cone.color = color(255, 255, 255, 0);
	cone = parse_object(fd, &cone);
	cone.direction = rotate_cone_angles(cone, cone.direction, 1);
	return (cone);
}

/*
** cylinder
** required structure
**
** cylinder {
** radius [radius]
** position [x] [y] [z]
** direction [x] [y] [z]
** color [r] [g] [b]
** angles [y_angle / longitude °] [x_angle / latitude °]
** }
*/

t_object		add_new_cylinder(int fd)
{
	t_object	cylinder;

	cylinder.typpe = CYLINDER;
	cylinder.txt_type = NONE;
	cylinder.bump_mapping = FLAT;
	cylinder.radius = 1;
	cylinder.direction = normalize_vector(vector(0, 0, 1));
	cylinder.point = point(0, 0, 0);
	cylinder.color = color(255, 255, 255, 0);
	cylinder = parse_object(fd, &cylinder);
	cylinder.direction = rotate_cylinder_angles(cylinder,
			cylinder.direction, 1);
	return (cylinder);
}

t_object		add_new_disc(int fd)
{
	t_object	disc;

	disc.typpe = DISC;
	disc.txt_type = NONE;
	disc.bump_mapping = FLAT;
	disc.normal = normalize_vector(vector(0, 1, 0));
	disc.point = point(0, 0, 0);
	disc.color = color(255, 255, 255, 0);
	disc.radius = 10;
	disc = parse_object(fd, &disc);
	return (disc);
}
