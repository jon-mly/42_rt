/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_parser_xml.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 16:10:48 by aabelque          #+#    #+#             */
/*   Updated: 2019/01/06 17:15:24 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	t_vector			rotate_for_angles(t_vector vect, t_camera camera)
{
	vect = vect_rotate_x(vect, camera.x_angle, 0);
	vect = vect_rotate_y(vect, camera.y_angle, 0);
	return (vect);
}

static	t_camera			get_default_camera_parameters(t_env *env)
{
	t_camera	camera;

	camera.width = 3;
	camera.height = 2;
	camera.plane_dist = 1.7;
	camera.spot = point(0, 0, 0);
	camera.direction = normalize_vector(vector(0, 0, 1));
	camera.posiition = vector(-camera.width / 2, camera.height / 2,
			camera.plane_dist);
	camera.horizontal_vect = vector(camera.width / (double)(env->win_width),
			0, 0);
	camera.vertical_vect = vector(0, -camera.height / (double)(env->win_height),
			0);
	return (camera);
}

static	t_camera			convert_camera_vector(t_camera camera)
{
	camera.horizontal_vect = rotate_for_angles(camera.horizontal_vect, camera);
	camera.vertical_vect = rotate_for_angles(camera.vertical_vect, camera);
	camera.direction = rotate_for_angles(camera.direction, camera);
	camera.posiition = rotate_for_angles(camera.posiition, camera);
	camera.up_left_corner =
		point(camera.spot.x + camera.posiition.x,
		camera.spot.y + camera.posiition.y,
		camera.spot.z + camera.posiition.z);
	return (camera);
}

t_camera					set_camera_xml(int fd, t_env *env)
{
	t_camera	camera;
	char		**line;

	camera = get_default_camera_parameters(env);
	while ((line = split_new_line(fd, env->chx))
			&& ft_strequ(line[0], "</camera>") == FALSE)
	{
		if (line_len(line) == 5 && ft_strequ(line[0], "\t<position>"))
			camera.spot = point(ft_atoi(line[1]), ft_atoi(line[2]),
				ft_atoi(line[3]));
		else if (line_len(line) == 4 && ft_strequ(line[0], "\t<angles>"))
		{
			camera.x_angle = degrees_to_radian(ft_atoi(line[1]));
			camera.y_angle = degrees_to_radian(ft_atoi(line[2]));
		}
		clear_line(line);
	}
	clear_line(line);
	camera = convert_camera_vector(camera);
	return (camera);
}
