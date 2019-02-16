/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 15:41:10 by aabelque          #+#    #+#             */
/*   Updated: 2019/02/16 17:09:11 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void		parse_object5(t_object *object, char **line)
{
	if (line_len(line) == 2 && ft_strequ(line[0], "texture"))
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
	if (line_len(line) == 2 && ft_strequ(line[0], "refraction_index"))
		object->refraction = fmax(ft_atoi(line[1]), 100.0) / 100.0;
	else if (line_len(line) == 1 && ft_strequ(line[0], "finite"))
		object->finite = 1;
	else if (line_len(line) == 1 && ft_strequ(line[0], "covered"))
		object->covered = 1;
	else if (line_len(line) == 2 && ft_strequ(line[0], "height"))
		object->height = ft_atof(line[1]);
	else if (line_len(line) == 2 && ft_strequ(line[0], "width"))
		object->width = ft_atof(line[1]);
	else if (line_len(line) == 2 && ft_strequ(line[0], "rho"))
		object->rho = ft_atof(line[1]);
	else if (line_len(line) == 2 && ft_strequ(line[0], "sigma"))
		object->sigma = ft_atof(line[1]);
	else if (line_len(line) == 2 && ft_strequ(line[0], "tau"))
		object->tau = ft_atof(line[1]);
}

static	void		parse_object3(t_object *object, char **line)
{
	if (line_len(line) == 4 && ft_strequ(line[0], "normal"))
		object->normal = normalize_vector(vector(ft_atof(line[1]),
					ft_atof(line[2]), ft_atof(line[3])));
	else if (line_len(line) == 2 && ft_strequ(line[0], "pi_divider"))
		object->angle = M_PI / ft_atof(line[1]);
	else if (line_len(line) == 4 && ft_strequ(line[0], "direction"))
		object->direction = normalize_vector(vector(ft_atof(line[1]),
					ft_atof(line[2]), ft_atof(line[3])));
	else if (line_len(line) == 3 && ft_strequ(line[0], "angles"))
	{
		object->y_angle = degrees_to_radian(ft_atof(line[1]));
		object->x_angle = degrees_to_radian(ft_atof(line[2]));
	}
	else if (line_len(line) == 2 && ft_strequ(line[0], "diffuse"))
		object->diffuse = fmin(fmax(ft_atof(line[1]) / 100.0, 0), 1);
	else if (line_len(line) == 2 && ft_strequ(line[0], "brillance"))
		object->brillance = fmin(fmax(ft_atof(line[1]) / 100.0, 0), 1);
	else if (line_len(line) == 2 && ft_strequ(line[0], "reflect"))
		object->reflection = fmin(fmax(ft_atof(line[1]) / 100.0, 0), 1);
	else if (line_len(line) == 2 && ft_strequ(line[0], "transparency"))
		object->transparency = fmin(fmax(ft_atof(line[1]) / 100.0, 0), 1);
}

static	void		parse_object2(t_object *object, char **line)
{
	if (line_len(line) == 4 && ft_strequ(line[0], "color"))
		object->color = color(ft_atof(line[1]), ft_atof(line[2]),
				ft_atof(line[3]), 0);
	else if (line_len(line) == 4 && ft_strequ(line[0], "position"))
		object->point = point(ft_atof(line[1]), ft_atof(line[2]),
				ft_atof(line[3]));
	else if (line_len(line) == 4 && ft_strequ(line[0], "point"))
		object->point = point(ft_atof(line[1]), ft_atof(line[2]),
				ft_atof(line[3]));
	else if (line_len(line) == 4 && ft_strequ(line[0], "first_vector"))
		object->first_vect = point(ft_atof(line[1]), ft_atof(line[2]),
				ft_atof(line[3]));
	else if (line_len(line) == 4 && ft_strequ(line[0], "second_vector"))
		object->second_vect = point(ft_atof(line[1]), ft_atof(line[2]),
				ft_atof(line[3]));
	else if (line_len(line) == 2 && ft_strequ(line[0], "radius"))
		object->radius = ft_atof(line[1]);
	else if (line_len(line) == 4 && ft_strequ(line[0], "center"))
		object->center = point(ft_atof(line[1]), ft_atof(line[2]),
				ft_atof(line[3]));
}

t_object			parse_object(int fd, t_object *obj, int chx)
{
	char		**line;

	obj->finite = 0;
	obj->covered = 0;
	while ((line = split_new_line(fd, chx)) && !ft_strequ(line[0], "}"))
	{
		parse_object2(obj, line);
		parse_object3(obj, line);
		parse_object4(obj, line);
		parse_object5(obj, line);
		if (line_len(line) == 2 && ft_strequ(line[0], "bump_mapping"))
		{
			if (ft_strequ(line[1], "VERTICAL_SIN"))
				obj->bump_mapping = VERTICAL_SIN;
			else if (ft_strequ(line[1], "HORIZONTAL_SIN"))
				obj->bump_mapping = HORIZONTAL_SIN;
		}
		clear_line(line);
	}
	obj->color.a = 255.0 * obj->transparency;
	parse_obj_help(obj);
	clear_line(line);
	return (*obj);
}
