/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 13:38:30 by aabelque          #+#    #+#             */
/*   Updated: 2018/11/05 13:38:45 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_object        parse_object(int fd, t_object *object)
{
	char		**line;

	object->finite = 0;
	object->covered = 0;
    while ((line = split_new_line(fd)) && !ft_strequ(line[0], "}"))
	{
		if (line_len(line) == 4 && ft_strequ(line[0], "color"))
			object->color = color(ft_atoi(line[1]), ft_atoi(line[2]),
						ft_atoi(line[3]), 0);
        else if (line_len(line) == 4 && ft_strequ(line[0], "position"))
			object->point = point(ft_atoi(line[1]), ft_atoi(line[2]),
							ft_atoi(line[3]));
        else if (line_len(line) == 4 && ft_strequ(line[0], "point"))
			object->point = point(ft_atoi(line[1]), ft_atoi(line[2]),
					ft_atoi(line[3]));
		else if (line_len(line) == 4 && ft_strequ(line[0], "first_vector"))
			object->first_vect = point(ft_atoi(line[1]), ft_atoi(line[2]),
					ft_atoi(line[3]));
		else if (line_len(line) == 4 && ft_strequ(line[0], "second_vector"))
			object->second_vect = point(ft_atoi(line[1]), ft_atoi(line[2]),
					ft_atoi(line[3]));
        else if (line_len(line) == 2 && ft_strequ(line[0], "radius"))
			object->radius = ft_atoi(line[1]);
        else if (line_len(line) == 4 && ft_strequ(line[0], "center"))
			object->center = point(ft_atoi(line[1]), ft_atoi(line[2]),
					ft_atoi(line[3]));
        else if (line_len(line) == 4 && ft_strequ(line[0], "normal"))
			object->normal = normalize_vector(vector(ft_atoi(line[1]),
						ft_atoi(line[2]), ft_atoi(line[3])));
        else if (line_len(line) == 2 && ft_strequ(line[0], "pi_divider"))
			object->angle = M_PI / ft_atoi(line[1]);
        else if (line_len(line) == 4 && ft_strequ(line[0], "direction"))
			object->direction = normalize_vector(vector(ft_atoi(line[1]),
						ft_atoi(line[2]), ft_atoi(line[3])));
        else if (line_len(line) == 3 && ft_strequ(line[0], "angles"))
		{
			object->y_angle = degrees_to_radian(ft_atoi(line[1]));
			object->x_angle = degrees_to_radian(ft_atoi(line[2]));
		}
		else if (line_len(line) == 2 && ft_strequ(line[0], "diffuse"))
			object->diffuse = fmin(fmax(ft_atoi(line[1]) / 100.0, 0), 1);
		else if (line_len(line) == 2 && ft_strequ(line[0], "brillance"))
			object->brillance = fmin(fmax(ft_atoi(line[1]) / 100.0, 0), 1);
		else if (line_len(line) == 2 && ft_strequ(line[0], "reflect"))
			object->reflection = fmin(fmax(ft_atoi(line[1]) / 100.0, 0), 1);
		else if (line_len(line) == 2 && ft_strequ(line[0], "transparency"))
			object->transparency = fmin(fmax(ft_atoi(line[1]) / 100.0, 0), 1);
		else if (line_len(line) == 2 && ft_strequ(line[0], "refraction_index"))
			object->refraction = fmax(ft_atoi(line[1]), 1) / 100.0;
		else if (line_len(line) == 1 && ft_strequ(line[0], "finite"))
			object->finite = 1;
		else if (line_len(line) == 1 && ft_strequ(line[0], "covered"))
			object->covered = 1;
		else if (line_len(line) == 2 && ft_strequ(line[0], "height"))
			object->height = (float)ft_atoi(line[1]);
		else if (line_len(line) == 2 && ft_strequ(line[0], "width"))
			object->width = (float)ft_atoi(line[1]);
		clear_line(line);
	}
	clear_line(line);
    return (*object);
}
