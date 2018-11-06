#include "rtv1.h"

t_object        parse_object(int fd, t_object *object)
{
	char		**line;

	object->finite = 0;
	object->covered = 0;
    while ((line = split_new_line(fd)) && !ft_strequ(line[0], "}"))
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
        else if (line_len(line) == 4 && ft_strequ(line[0], "normal"))
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
		else if (line_len(line) == 2 && ft_strequ(line[0], "refraction_index"))
			object->refraction = fmax(ft_atof(line[1]), 1) / 100.0;
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
		else if (line_len(line) == 2 && ft_strequ(line[0], "texture"))
		{
			if (ft_strequ(line[1], "CHECKER"))
				object->texture_type = CHECKER;
			else if (ft_strequ(line[1], "HORIZONTAL_CIRCLE"))
				object->texture_type = HORIZONTAL_CIRCLE;
			else if (ft_strequ(line[1], "VERTICAL_CIRCLE"))
				object->texture_type = VERTICAL_CIRCLE;
			else if (ft_strequ(line[1], "DOTS"))
				object->texture_type = DOTS;
			else if (ft_strequ(line[1], "DOTS_REVERTED"))
				object->texture_type = DOTS_REVERTED;
			else if (ft_strequ(line[1], "DOTS_CROWN"))
				object->texture_type = DOTS_CROWN;
			else if (ft_strequ(line[1], "DOTS_REVERTED_CROWN"))
				object->texture_type = DOTS_REVERTED_CROWN;
			else if (ft_strequ(line[1], "PERLIN"))
				object->texture_type = PERLIN;
			else if (ft_strequ(line[1], "WOOD"))
				object->texture_type = WOOD;
			else if (ft_strequ(line[1], "MARBLE"))
				object->texture_type = MARBLE;
		}
		else if (line_len(line) == 2 && ft_strequ(line[0], "bump_mapping"))
		{
			if (ft_strequ(line[1], "VERTICAL_SIN"))
				object->bump_mapping = VERTICAL_SIN;
			else if (ft_strequ(line[1], "HORIZONTAL_SIN"))
				object->bump_mapping = HORIZONTAL_SIN;
		}
		clear_line(line);
	}
	object->color.a = 255.0 * object->transparency;
	if (object->texture_type == CHECKER || object->texture_type == HORIZONTAL_CIRCLE
		|| object->texture_type == VERTICAL_CIRCLE || object->texture_type == DOTS
		|| object->texture_type == DOTS_REVERTED || object->texture_type == DOTS_CROWN
		|| object->texture_type ==  DOTS_REVERTED_CROWN)
		object->texture_algo = PROCEDURAL;
	else if (object->texture_type == PERLIN || object->texture_type == WOOD
		|| object->texture_type == MARBLE)
		object->texture_algo = PERLIN_ALGO;
	else
		object->texture_algo = NO_ALGO;
	clear_line(line);
    return (*object);
}