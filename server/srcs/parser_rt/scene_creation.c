/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 16:48:17 by jmlynarc          #+#    #+#             */
/*   Updated: 2019/02/16 17:11:16 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			extend_scene2(int fd, t_scene *scene, char **line, int chx)
{
	scene->objects_count++;
	scene->objects = expand_objects(scene->objects, scene->objects_count);
	scene->objects[scene->objects_count - 1] = add_new_object(fd, line[0], chx);
	scene->objects[scene->objects_count - 1].id = scene->objects_count - 1;
	scene->objects[scene->objects_count - 1].index = scene->objects_count - 1;
	if (scene->objects[scene->objects_count - 1].finite
			&& scene->objects[scene->objects_count - 1].covered)
		*scene =
			create_dependant_objects(scene->objects[scene->objects_count - 1],
					*scene, scene->objects_count - 1);
}

static t_scene		extend_scene(int fd, t_scene scene, char **line, t_env *env)
{
	if (ft_strequ(line[0], "theme") && line_len(line) == 4)
		scene.theme = color(ft_atoi(line[1]), ft_atoi(line[2]),
				ft_atoi(line[3]), 0);
	else if (ft_strequ(line[0], "power") && line_len(line) == 2)
		scene.power = fmin(fmax((float)ft_atoi(line[1]) / 100.0, 0), 1);
	if (line_len(line) != 2 || !(ft_strequ(line[1], "{")))
		return (scene);
	if (ft_strequ(line[0], "light"))
	{
		scene.lights_count++;
		scene.lights = add_light(fd, scene.lights, scene.lights_count,
				env->chx);
	}
	else if (ft_strequ(line[0], "sphere") || ft_strequ(line[0], "cone") ||
			ft_strequ(line[0], "cylinder") || ft_strequ(line[0], "plane") ||
			ft_strequ(line[0], "disc") || ft_strequ(line[0], "rectangle") ||
			ft_strequ(line[0], "triangle") ||
			ft_strequ(line[0], "parallelogram") ||
			ft_strequ(line[0], "hyperboloid"))
		extend_scene2(fd, &scene, line, env->chx);
	else if (ft_strequ(line[0], "camera"))
		env->camera = set_camera(fd, env);
	return (scene);
}

t_scene				create_scene(t_env *env, int fd)
{
	char			**line;
	t_scene			scene;

	scene.objects_count = 0;
	scene.objects = NULL;
	scene.lights_count = 0;
	scene.lights = NULL;
	scene.theme = color(255, 255, 255, 0);
	scene.power = 0.25;
	scene.sett = env->scene.sett;
	while ((line = split_new_line(fd, env->chx)))
	{
		scene = extend_scene(fd, scene, line, env);
		clear_line(line);
	}
	clear_line(line);
	return (scene);
}
