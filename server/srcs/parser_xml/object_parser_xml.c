/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parser_xml.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 16:10:59 by aabelque          #+#    #+#             */
/*   Updated: 2019/02/16 17:05:08 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void		parse_object5(t_object *object, char **line)
{
	if (line_len(line) == 3 && ft_strequ(line[0], "\t<texture>"))
	{
		if (ft_strequ(line[1], "CHECKER"))
			object->txt_type = CHECKER;
		else if (ft_strequ(line[1], "HORIZONTAL_CIRCLE"))
			object->txt_type = HORIZONTAL_CIRCLE;
		else if (ft_strequ(line[1], "VERTICAL_CIRCLE"))
			object->txt_type = VERTICAL_CIRCLE;
		else if (ft_strequ(line[1], "DOTS"))
			object->txt_type = DOTS;
		else if (ft_strequ(line[1], "DOTS_REVERTED"))
			object->txt_type = DOTS_REVERTED;
		else if (ft_strequ(line[1], "DOTS_CROWN"))
			object->txt_type = DOTS_CROWN;
		else if (ft_strequ(line[1], "DOTS_REVERTED_CROWN"))
			object->txt_type = DOTS_REVERTED_CROWN;
		else if (ft_strequ(line[1], "PERLIN"))
			object->txt_type = PERLIN;
		else if (ft_strequ(line[1], "WOOD"))
			object->txt_type = WOOD;
		else if (ft_strequ(line[1], "MARBLE"))
			object->txt_type = MARBLE;
	}
}

static	void		parse_object4(t_object *object, char **line)
{
	if (line_len(line) == 3 && ft_strequ(line[0], "\t<refraction_index>"))
		object->refraction = fmax(ft_atof(line[1]), 1) / 100.0;
	else if (line_len(line) == 3 && ft_strequ(line[0], "\t<finite>"))
		object->finite = ft_atoi(line[1]);
	else if (line_len(line) == 3 && ft_strequ(line[0], "\t<covered>"))
		object->covered = ft_atoi(line[1]);
	else if (line_len(line) == 3 && ft_strequ(line[0], "\t<height>"))
		object->height = ft_atof(line[1]);
	else if (line_len(line) == 3 && ft_strequ(line[0], "\t<width>"))
		object->width = ft_atof(line[1]);
	else if (line_len(line) == 3 && ft_strequ(line[0], "\t<rho>"))
		object->rho = ft_atof(line[1]);
	else if (line_len(line) == 3 && ft_strequ(line[0], "\t<sigma>"))
		object->sigma = ft_atof(line[1]);
	else if (line_len(line) == 3 && ft_strequ(line[0], "\t<tau>"))
		object->tau = ft_atof(line[1]);
}

static	void		parse_object3(t_object *object, char **line)
{
	if (line_len(line) == 5 && ft_strequ(line[0], "\t<normal>"))
		object->normal = normalize_vector(vector(ft_atof(line[1]),
					ft_atof(line[2]), ft_atof(line[3])));
	else if (line_len(line) == 3 && ft_strequ(line[0], "\t<pi_divider>"))
		object->angle = M_PI / ft_atof(line[1]);
	else if (line_len(line) == 5 && ft_strequ(line[0], "\t<direction>"))
		object->direction = normalize_vector(vector(ft_atof(line[1]),
					ft_atof(line[2]), ft_atof(line[3])));
	else if (line_len(line) == 4 && ft_strequ(line[0], "\t<angles>"))
	{
		object->y_angle = degrees_to_radian(ft_atof(line[1]));
		object->x_angle = degrees_to_radian(ft_atof(line[2]));
	}
	else if (line_len(line) == 3 && ft_strequ(line[0], "\t<diffuse>"))
		object->diffuse = fmin(fmax(ft_atof(line[1]) / 100.0, 0), 1);
	else if (line_len(line) == 3 && ft_strequ(line[0], "\t<brillance>"))
		object->brillance = fmin(fmax(ft_atof(line[1]) / 100.0, 0), 1);
	else if (line_len(line) == 3 && ft_strequ(line[0], "\t<reflect>"))
		object->reflection = fmin(fmax(ft_atof(line[1]) / 100.0, 0), 1);
	else if (line_len(line) == 3 && ft_strequ(line[0], "\t<transparency>"))
		object->transparency = fmin(fmax(ft_atof(line[1]) / 100.0, 0), 1);
}

static	void		parse_object2(t_object *object, char **line)
{
	if (line_len(line) == 5 && ft_strequ(line[0], "\t<color>"))
		object->color = color(ft_atof(line[1]), ft_atof(line[2]),
				ft_atof(line[3]), 0);
	else if (line_len(line) == 5 && ft_strequ(line[0], "\t<position>"))
		object->point = point(ft_atof(line[1]), ft_atof(line[2]),
				ft_atof(line[3]));
	else if (line_len(line) == 5 && ft_strequ(line[0], "\t<point>"))
		object->point = point(ft_atof(line[1]), ft_atof(line[2]),
				ft_atof(line[3]));
	else if (line_len(line) == 5 && ft_strequ(line[0], "\t<first_vector>"))
		object->first_vect = point(ft_atof(line[1]), ft_atof(line[2]),
				ft_atof(line[3]));
	else if (line_len(line) == 5 && ft_strequ(line[0], "\t<second_vector>"))
		object->second_vect = point(ft_atof(line[1]), ft_atof(line[2]),
				ft_atof(line[3]));
	else if (line_len(line) == 3 && ft_strequ(line[0], "\t<radius>"))
		object->radius = ft_atof(line[1]);
	else if (line_len(line) == 5 && ft_strequ(line[0], "\t<center>"))
		object->center = point(ft_atof(line[1]), ft_atof(line[2]),
				ft_atof(line[3]));
}

t_object			parse_object_xml(int fd, t_object *obj, int chx)
{
	char		**line;

	obj->finite = 0;
	obj->covered = 0;
	while ((line = split_new_line(fd, chx)) && (line[0][1] != '/'))
	{
		parse_object2(obj, line);
		parse_object3(obj, line);
		parse_object4(obj, line);
		parse_object5(obj, line);
		if (line_len(line) == 3 && ft_strequ(line[0], "\t<bump_mapping>"))
		{
			if (ft_strequ(line[1], "VERTICAL_SIN"))
				obj->bump_mapping = VERTICAL_SIN;
			else if (ft_strequ(line[1], "HORIZONTAL_SIN"))
				obj->bump_mapping = HORIZONTAL_SIN;
		}
		clear_line(line);
	}
	obj->color.a = 255.0 * obj->transparency;
	parse_obj_help_xml(obj);
	clear_line(line);
	return (*obj);
}
