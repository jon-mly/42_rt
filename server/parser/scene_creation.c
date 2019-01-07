/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 16:48:17 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/08/23 14:56:09 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Read the file given in parameter that describes the scene. When keywords are
** read (objects name or light), functions are called to extend the scene with
** objects or lights.
** By default, the scene is empty.
*/

t_object		*expand_objects(t_object *objects, int previous_count)
{
	t_object		*new_list;
	int				i;

	if (!(new_list = (t_object*)malloc(sizeof(t_object)
					* (previous_count + 1))))
		return (NULL);
	if (objects)
	{
		i = -1;
		while (++i < previous_count)
			new_list[i] = objects[i];
		ft_memdel((void**)&objects);
	}
	return (new_list);
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
		scene.lights = add_light(fd, scene.lights, scene.lights_count);
	}
	else if (ft_strequ(line[0], "sphere") || ft_strequ(line[0], "cone") ||
		ft_strequ(line[0], "cylinder") || ft_strequ(line[0], "plane") ||
		ft_strequ(line[0], "disc") || ft_strequ(line[0], "rectangle") ||
		ft_strequ(line[0], "triangle") | ft_strequ(line[0], "parallelogram") ||
		ft_strequ(line[0], "hyperboloid"))
	{
		scene.objects_count++;
		scene.objects = expand_objects(scene.objects, scene.objects_count);
		scene.objects[scene.objects_count - 1] = add_new_object(fd, line[0]);
		scene.objects[scene.objects_count - 1].id = scene.objects_count - 1;
		scene.objects[scene.objects_count - 1].index = scene.objects_count - 1;
		if (scene.objects[scene.objects_count - 1].finite && scene.objects[scene.objects_count - 1].covered)
			scene = create_dependant_objects(scene.objects[scene.objects_count - 1], fd, scene,
			scene.objects_count - 1);
	}
	else if (ft_strequ(line[0], "camera"))
		env->camera = set_camera(fd, env);
	return (scene);
}

t_scene				create_scene(t_env *env, char *file_name, int fd)
{
	char		**line;
	t_scene		scene;

	scene.objects_count = 0;
	scene.objects = NULL;
	scene.lights_count = 0;
	scene.lights = NULL;
	scene.theme = color(255, 255, 255, 0);
	scene.power = 0.25;
	while ((line = split_new_line(fd)))
	{
		scene = extend_scene(fd, scene, line, env);
		clear_line(line);
	}
	clear_line(line);
	return (scene);
}
