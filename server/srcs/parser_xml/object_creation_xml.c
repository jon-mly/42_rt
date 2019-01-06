/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_creation_xml.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 16:10:13 by aabelque          #+#    #+#             */
/*   Updated: 2019/01/06 17:40:42 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_object		add_new_rectangle(int fd, int chx)
{
	t_object	rectangle;

	rectangle.typpe = RECTANGLE;
	rectangle.txt_type = NONE;
	rectangle.bump_mapping = FLAT;
	rectangle.color = color(255, 255, 255, 0);
	rectangle.x_angle = 0;
	rectangle.y_angle = 0;
	rectangle.normal = vector(0, 1, 0);
	rectangle.width = 0;
	rectangle.height = 0;
	rectangle = parse_object_xml(fd, &rectangle, chx);
	rectangle.normal = rotate_vector_angles(rectangle, rectangle.normal, 1);
	return (rectangle);
}

static t_object		add_new_triangle(int fd, int chx)
{
	t_object	triangle;

	triangle.typpe = TRIANGLE;
	triangle.txt_type = NONE;
	triangle.bump_mapping = FLAT;
	triangle.color = color(255, 255, 255, 0);
	triangle.first_vect = vector(1, 0, 0);
	triangle.second_vect = vector(0, 0, 1);
	triangle.point = point(0, 0, 0);
	triangle = parse_object_xml(fd, &triangle, chx);
	triangle.normal = normalize_vector(cross_product(triangle.first_vect,
				triangle.second_vect));
	return (triangle);
}

static t_object		add_new_parallelogram(int fd, int chx)
{
	t_object	parall;

	parall.typpe = PARALLELOGRAM;
	parall.txt_type = NONE;
	parall.bump_mapping = FLAT;
	parall.color = color(255, 255, 255, 0);
	parall.first_vect = vector(1, 0, 0);
	parall.second_vect = vector(0, 0, 1);
	parall.point = point(0, 0, 0);
	parall = parse_object_xml(fd, &parall, chx);
	parall.normal = normalize_vector(cross_product(parall.first_vect,
				parall.second_vect));
	return (parall);
}

static t_object		add_new_hyperboloid(int fd, int chx)
{
	t_object	hyperboloid;

	hyperboloid.typpe = HYPERBOLOID;
	hyperboloid.txt_type = NONE;
	hyperboloid.bump_mapping = FLAT;
	hyperboloid.color = color(255, 255, 255, 0);
	hyperboloid.center = point(0, 0, 0);
	hyperboloid.y_angle = 0;
	hyperboloid.x_angle = 0;
	hyperboloid = parse_object_xml(fd, &hyperboloid, chx);
	return (hyperboloid);
}

t_object			add_new_object_xml(int fd, char *type, int chx)
{
	if (ft_strequ(type, "<cylinder>"))
		return (add_new_cylinder_xml(fd, chx));
	else if (ft_strequ(type, "<sphere>"))
		return (add_new_sphere_xml(fd, chx));
	else if (ft_strequ(type, "<plane>"))
		return (add_new_plane_xml(fd, chx));
	else if (ft_strequ(type, "<disc>"))
		return (add_new_disc_xml(fd, chx));
	else if (ft_strequ(type, "<rectangle>"))
		return (add_new_rectangle(fd, chx));
	else if (ft_strequ(type, "<triangle>"))
		return (add_new_triangle(fd, chx));
	else if (ft_strequ(type, "<parallelogram>"))
		return (add_new_parallelogram(fd, chx));
	else if (ft_strequ(type, "<hyperboloid>"))
		return (add_new_hyperboloid(fd, chx));
	else
		return (add_new_cone_xml(fd, chx));
}
