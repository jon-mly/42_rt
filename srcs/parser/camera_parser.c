/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 14:31:37 by aabelque          #+#    #+#             */
/*   Updated: 2018/08/23 17:52:39 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

t_camera					set_camera(int fd, t_env *env)
{
	t_camera	camera;
	char		**line;
	double		len;

	camera = get_default_camera_parameters(env);
	while ((line = split_new_line(fd)) && line[0] != NULL)
	{
		len = line_len(line);
		if (len == 4 && ft_strequ(line[0], "\t[position]"))
			camera.spot = point((float)ft_atof(line[1]), (float)ft_atof(line[2]),
				(float)ft_atof(line[3]));
		else if (len == 3 && ft_strequ(line[0], "\t[angles]"))
		{
			camera.x_angle = degrees_to_radian((float)ft_atof(line[1]));
			camera.y_angle = degrees_to_radian((float)ft_atof(line[2]));
		}
		printf("%f||%f||%f\n", camera.spot.x, camera.spot.y, camera.spot.z);
		clear_line(line);
	}
	clear_line(line);
	camera = convert_camera_vector(camera);
	return (camera);
}
