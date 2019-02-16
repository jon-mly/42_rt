/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_creation2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 12:00:40 by aabelque          #+#    #+#             */
/*   Updated: 2019/02/16 17:07:01 by aabelque         ###   ########.fr       */
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

t_object		add_new_sphere(int fd, int chx)
{
	t_object	sphere;

	sphere = get_template_object();
	sphere.typpe = SPHERE;
	sphere = parse_object(fd, &sphere, chx);
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

t_object		add_new_plane(int fd, int chx)
{
	t_object	plane;

	plane = get_template_object();
	plane.typpe = PLANE;
	plane = parse_object(fd, &plane, chx);
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

t_object		add_new_cone(int fd, int chx)
{
	t_object	cone;

	cone = get_template_object();
	cone.direction = vector(0, 0, 1);
	cone.typpe = CONE;
	cone = parse_object(fd, &cone, chx);
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

t_object		add_new_cylinder(int fd, int chx)
{
	t_object	cylinder;

	cylinder = get_template_object();
	cylinder.direction = vector(0, 0, 1);
	cylinder.typpe = CYLINDER;
	cylinder = parse_object(fd, &cylinder, chx);
	cylinder.direction = rotate_cylinder_angles(cylinder,
			cylinder.direction, 1);
	return (cylinder);
}

t_object		add_new_disc(int fd, int chx)
{
	t_object	disc;

	disc = get_template_object();
	disc.typpe = DISC;
	disc = parse_object(fd, &disc, chx);
	return (disc);
}
