/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 15:36:32 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/08/11 11:08:31 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Add a new light to the list of lights that compose the scene to create.
** Takes the file descriptor of the file that is being read, and the pointer
** on the lights already created (NULL if empty).
** Realloc the pointer with the current lights + 1.
** If sone parameters are not precised, default values will be set.
*/

static t_light		*extend_lights(t_light **lights, int count)
{
	int			i;
	t_light		*new_lights;

	if (*lights == NULL)
	{
		if (!(*lights = (t_light*)malloc(sizeof(t_light))))
			return (NULL);
		return (*lights);
	}
	else
	{
		if (!(new_lights = (t_light*)malloc(sizeof(t_light) * (count + 1))))
			return (NULL);
		i = -1;
		while (++i < count)
			new_lights[i] = (*lights)[i];
		ft_memdel((void**)lights);
		*lights = new_lights;
		return (new_lights);
	}
}

/*
** light
** required structure (only omni type)
**
** light {
** position [x] [y] [z]
** color [r] [g] [b]
** }
*/

t_light				*add_light(int fd, t_light *existing_lights, int count)
{
	char		**line;
	t_light		new_light;

	existing_lights = extend_lights(&existing_lights, count - 1);
	new_light.typpe = OMNI;
	new_light.posiition = point(0, 0, 0);
	new_light.color = color(255, 255, 255, 0);
	new_light.power = 100.0;
	while ((line = split_new_line(fd)) && line[0] != NULL)
	{
		if (line_len(line) == 4 && ft_strequ(line[0], "\t[position]"))
			new_light.posiition = point((float)ft_atof(line[1]), (float)ft_atof(line[2]),
							(float)ft_atof(line[3]));
		else if (line_len(line) == 4 && ft_strequ(line[0], "\t[color]"))
			new_light.color = color((float)(float)ft_atof(line[1]), (float)ft_atof(line[2]),
						(float)ft_atof(line[3]), 0);
		else if (line_len(line) == 4 && ft_strequ(line[0], "\t[direction]"))
			new_light.direction = normalize_vector(vector((float)ft_atof(line[1]), (float)ft_atof(line[2]),
							(float)ft_atof(line[3])));
		else if (line_len(line) == 2 && ft_strequ(line[0], "\t[power]"))
			new_light.power = fmax((float)ft_atof(line[1]), 0);
		else if (line_len(line) == 2 && ft_strequ(line[0], "\t[angle]]"))
			new_light.angle = degrees_to_radian(fmax(fmin((float)ft_atof(line[1]), 90), 0));
		else if (line_len(line) == 2 && ft_strequ(line[0], "\t[type]"))
		{
			if (ft_strequ(line[1], "OMNI"))
				new_light.typpe = OMNI;
			else if (ft_strequ(line[1], "AMBIANT"))
				new_light.typpe = AMBIANT;
			else if (ft_strequ(line[1], "PROJECTOR"))
				new_light.typpe = PROJECTOR;
		}
		clear_line(line);
	}
	clear_line(line);
	existing_lights[count - 1] = new_light;
	return (existing_lights);
}
