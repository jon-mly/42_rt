/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 16:09:07 by jmlynarc          #+#    #+#             */
/*   Updated: 2019/01/07 14:33:12 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_object		add_new_rectangle(int fd, int chx)
{
	t_object	rectangle;

	rectangle = get_template_object();
	rectangle.typpe = RECTANGLE;
	rectangle.normal = vector(0, 1, 0);
	rectangle = parse_object(fd, &rectangle, chx);
	rectangle.normal = rotate_vector_angles(rectangle, rectangle.normal, 1);
	return (rectangle);
}

static t_object		add_new_triangle(int fd, int chx)
{
	t_object	triangle;

	triangle = get_template_object();
	triangle.typpe = TRIANGLE;
	triangle = parse_object(fd, &triangle, chx);
	triangle.normal = normalize_vector(cross_product(triangle.first_vect,
				triangle.second_vect));
	return (triangle);
}

static t_object		add_new_parallelogram(int fd, int chx)
{
	t_object	parall;

	parall = get_template_object();
	parall.typpe = PARALLELOGRAM;
	parall = parse_object(fd, &parall, chx);
	parall.normal = normalize_vector(cross_product(parall.first_vect,
				parall.second_vect));
	return (parall);
}

static t_object		add_new_hyperboloid(int fd, int chx)
{
	t_object	hyperboloid;

	hyperboloid = get_template_object();
	hyperboloid.typpe = HYPERBOLOID;
	hyperboloid = parse_object(fd, &hyperboloid, chx);
	return (hyperboloid);
}

t_object			add_new_object(int fd, char *type, int chx)
{
	if (ft_strequ(type, "cylinder"))
		return (add_new_cylinder(fd, chx));
	else if (ft_strequ(type, "sphere"))
		return (add_new_sphere(fd, chx));
	else if (ft_strequ(type, "plane"))
		return (add_new_plane(fd, chx));
	else if (ft_strequ(type, "disc"))
		return (add_new_disc(fd, chx));
	else if (ft_strequ(type, "rectangle"))
		return (add_new_rectangle(fd, chx));
	else if (ft_strequ(type, "triangle"))
		return (add_new_triangle(fd, chx));
	else if (ft_strequ(type, "parallelogram"))
		return (add_new_parallelogram(fd, chx));
	else if (ft_strequ(type, "hyperboloid"))
		return (add_new_hyperboloid(fd, chx));
	else
		return (add_new_cone(fd, chx));
}
