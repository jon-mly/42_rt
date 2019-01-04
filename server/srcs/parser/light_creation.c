/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 15:36:32 by jmlynarc          #+#    #+#             */
/*   Updated: 2019/01/04 16:18:53 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

static	t_light		add_light_help(t_light new_light, char **line)
{
	printf("light line = %d\n", line_len(line));
	printf("light line[0] = %s\n", line[0]);
	printf("light line[1] = %s\n", line[1]);
	if (line_len(line) == 5 && ft_strequ(line[0], "\t<position>"))
		new_light.posiition = point(ft_atoi(line[1]), ft_atoi(line[2]),
				ft_atoi(line[3]));
	else if (line_len(line) == 5 && ft_strequ(line[0], "\t<color>"))
		new_light.color = color(ft_atoi(line[1]), ft_atoi(line[2]),
				ft_atoi(line[3]), 0);
	else if (line_len(line) == 5 && ft_strequ(line[0], "\t<direction>"))
		new_light.direction = normalize_vector(vector(ft_atoi(line[1]),
					ft_atoi(line[2]), ft_atoi(line[3])));
	else if (line_len(line) == 3 && ft_strequ(line[0], "\t<power>"))
		new_light.power = fmax(ft_atoi(line[1]), 0);
	else if (line_len(line) == 3 && ft_strequ(line[0], "\t<angle>"))
		new_light.angle = degrees_to_radian(fmax(fmin(ft_atoi(line[1]), 90),
					0));
	else if (line_len(line) == 3 && ft_strequ(line[0], "\t<type>"))
	{
		if (ft_strequ(line[1], "OMNI"))
			new_light.typpe = OMNI;
		else if (ft_strequ(line[1], "AMBIANT"))
			new_light.typpe = AMBIANT;
		else if (ft_strequ(line[1], "PROJECTOR"))
			new_light.typpe = PROJECTOR;
	}
	return (new_light);
}

t_light				*add_light(int fd, t_light *existing_lights, int count)
{
	char		**line;
	t_light		new_light;

	existing_lights = extend_lights(&existing_lights, count - 1);
	new_light.typpe = OMNI;
	new_light.posiition = point(0, 0, 0);
	new_light.color = color(255, 255, 255, 0);
	new_light.power = 100.0;
	while ((line = split_new_line(fd)) && ft_strequ(line[0], "</light>") == FALSE)
	{
		new_light = add_light_help(new_light, line);
		clear_line(line);
	}
	clear_line(line);
	existing_lights[count - 1] = new_light;
	return (existing_lights);
}
