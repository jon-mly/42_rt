#include "rtv1.h"

t_object        parse_object(int fd, t_object *object)
{
	char		**line;
	int			len;

	object->finite = 0;
	object->covered = 0;
    while ((line = split_new_line(fd)) && line[0] != NULL)
	{
		len = line_len(line);
		if (len == 4 && ft_strequ(line[0], "\t[color]"))
			object->color = color((float)ft_atof(line[1]), (float)ft_atof(line[2]),
						(float)ft_atof(line[3]), 0);
        else if (len == 4 && ft_strequ(line[0], "\t[position]"))
			object->point = point((float)ft_atof(line[1]), (float)ft_atof(line[2]),
							(float)ft_atof(line[3]));
        else if (len == 4 && ft_strequ(line[0], "\t[point]"))
			object->point = point((float)ft_atof(line[1]), (float)ft_atof(line[2]),
					(float)ft_atof(line[3]));
		else if (len == 4 && ft_strequ(line[0], "\t[first_vector]"))
			object->first_vect = point((float)ft_atof(line[1]), (float)ft_atof(line[2]),
					(float)ft_atof(line[3]));
		else if (len == 4 && ft_strequ(line[0], "\t[second_vector]"))
			object->second_vect = point((float)ft_atof(line[1]), (float)ft_atof(line[2]),
					(float)ft_atof(line[3]));
        else if (len == 2 && ft_strequ(line[0], "\t[radius]"))
			object->radius = (float)ft_atof(line[1]);
        else if (len == 4 && ft_strequ(line[0], "\t[center]"))
			object->center = point((float)ft_atof(line[1]), (float)ft_atof(line[2]),
					(float)ft_atof(line[3]));
        else if (len == 4 && ft_strequ(line[0], "\t[normal]"))
			object->normal = normalize_vector(vector((float)ft_atof(line[1]),
						(float)ft_atof(line[2]), (float)ft_atof(line[3])));
        else if (len == 2 && ft_strequ(line[0], "\t[pi_divider]"))
			object->angle = M_PI / (float)ft_atof(line[1]);
        else if (len == 4 && ft_strequ(line[0], "\t[direction]"))
			object->direction = normalize_vector(vector((float)ft_atof(line[1]),
						(float)ft_atof(line[2]), (float)ft_atof(line[3])));
        else if (len == 3 && ft_strequ(line[0], "\t[angles]"))
		{
			object->y_angle = degrees_to_radian((float)ft_atof(line[1]));
			object->x_angle = degrees_to_radian((float)ft_atof(line[2]));
		}
		else if (len == 2 && ft_strequ(line[0], "\t[diffuse]"))
			object->diffuse = fmin(fmax((float)ft_atof(line[1]) / 100.0, 0), 1);
		else if (len == 2 && ft_strequ(line[0], "\t[brillance]"))
			object->brillance = fmin(fmax((float)ft_atof(line[1]) / 100.0, 0), 1);
		else if (len == 2 && ft_strequ(line[0], "\t[reflect]"))
			object->reflection = fmin(fmax((float)ft_atof(line[1]) / 100.0, 0), 1);
		else if (len == 2 && ft_strequ(line[0], "\t[transparency]"))
			object->transparency = fmin(fmax((float)ft_atof(line[1]) / 100.0, 0), 1);
		else if (len == 2 && ft_strequ(line[0], "\t[refraction_index]"))
			object->refraction = fmax((float)ft_atof(line[1]), 1) / 100.0;
		else if (len == 1 && ft_strequ(line[0], "\t[finite"))
			object->finite = 1;
		else if (len == 1 && ft_strequ(line[0], "\t[covered]"))
			object->covered = 1;
		else if (len == 2 && ft_strequ(line[0], "\t[height]"))
			object->height = (float)ft_atof(line[1]);
		else if (len == 2 && ft_strequ(line[0], "\t[width]"))
			object->width = (float)ft_atof(line[1]);
		clear_line(line);
	}
	clear_line(line);
    return (*object);
}