/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 16:09:07 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/12/21 17:41:07 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_object		add_new_rectangle(int fd)
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
	rectangle = parse_object(fd, &rectangle);
	rectangle.normal = rotate_vector_angles(rectangle, rectangle.normal, 1);
	return (rectangle);
}

static t_object		add_new_triangle(int fd)
{
	t_object	triangle;

	triangle.typpe = TRIANGLE;
	triangle.txt_type = NONE;
	triangle.bump_mapping = FLAT;
	triangle.color = color(255, 255, 255, 0);
	triangle.first_vect = vector(1, 0, 0);
	triangle.second_vect = vector(0, 0, 1);
	triangle.point = point(0, 0, 0);
	triangle = parse_object(fd, &triangle);
	triangle.normal = normalize_vector(cross_product(triangle.first_vect,
				triangle.second_vect));
	return (triangle);
}

static t_object		add_new_parallelogram(int fd)
{
	t_object	parall;

	parall.typpe = PARALLELOGRAM;
	parall.txt_type = NONE;
	parall.bump_mapping = FLAT;
	parall.color = color(255, 255, 255, 0);
	parall.first_vect = vector(1, 0, 0);
	parall.second_vect = vector(0, 0, 1);
	parall.point = point(0, 0, 0);
	parall = parse_object(fd, &parall);
	parall.normal = normalize_vector(cross_product(parall.first_vect,
				parall.second_vect));
	return (parall);
}

static t_object		add_new_hyperboloid(int fd)
{
	t_object	hyperboloid;

	hyperboloid.typpe = HYPERBOLOID;
	hyperboloid.txt_type = NONE;
	hyperboloid.bump_mapping = FLAT;
	hyperboloid.color = color(255, 255, 255, 0);
	hyperboloid.center = point(0, 0, 0);
	hyperboloid.y_angle = 0;
	hyperboloid.x_angle = 0;
	hyperboloid = parse_object(fd, &hyperboloid);
	return (hyperboloid);
}

t_object			add_new_object(int fd, char *type)
{
	if (ft_strequ(type, "cylinder"))
		return (add_new_cylinder(fd));
	else if (ft_strequ(type, "sphere"))
		return (add_new_sphere(fd));
	else if (ft_strequ(type, "plane"))
		return (add_new_plane(fd));
	else if (ft_strequ(type, "disc"))
		return (add_new_disc(fd));
	else if (ft_strequ(type, "rectangle"))
		return (add_new_rectangle(fd));
	else if (ft_strequ(type, "triangle"))
		return (add_new_triangle(fd));
	else if (ft_strequ(type, "parallelogram"))
		return (add_new_parallelogram(fd));
	else if (ft_strequ(type, "hyperboloid"))
		return (add_new_hyperboloid(fd));
	else
		return (add_new_cone(fd));
}
