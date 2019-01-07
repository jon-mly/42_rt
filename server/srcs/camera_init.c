/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:10 by jmlynarc          #+#    #+#             */
/*   Updated: 2019/01/03 15:03:37 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Initialize a default camera before parsing the file describing the scene.
*/

t_camera	init_camera(t_env *env)
{
	t_camera	camera;

	camera.width = 1.5;
	camera.height = 1;
	camera.plane_dist = 0.8;
	camera.spot = point(0, 0, 0);
	camera.direction = normalize_vector(vector(0, 0, 1));
	camera.posiition = vector(camera.spot.x
			+ camera.direction.x - camera.width / 2,
			camera.spot.y + camera.direction.y + camera.height / 2,
			camera.spot.z + camera.direction.z);
	camera.up_left_corner = camera.posiition;
	camera.horizontal_step = camera.width / (double)(env->win_width);
	camera.vertical_step = camera.height / (double)(env->win_height);
	return (camera);
}
