/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 16:47:21 by aabelque          #+#    #+#             */
/*   Updated: 2019/02/16 17:13:25 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		setup_window(t_env *env)
{
	int		bpp;
	int		s_l;
	int		endian;

	env->mlx_ptr = mlx_init();
	env->win_width = env->scene.sett.render_w;
	env->win_height = env->scene.sett.render_h;
	env->win_ptr = mlx_new_window(env->mlx_ptr, env->win_width, env->win_height,
		"RT");
	if (env->mlx_ptr == NULL || env->win_ptr == NULL)
		exit_error(env);
	env->img_ptr = mlx_new_image(env->mlx_ptr, env->win_width, env->win_height);
	env->img_width = env->win_width;
	env->img_height = env->win_height;
	env->img_str = mlx_get_data_addr(env->img_ptr, &bpp, &s_l,
		&endian);
	if (env->img_ptr == NULL || env->img_str == NULL)
		exit_error(env);
	env->line_size = s_l / 4;
	env->bpp = bpp;
	env->endian = endian;
}

t_env			*init_env(t_env *env, char *file_name)
{
	int		fd;

	if ((fd = open(file_name, O_RDONLY)) <= 2)
		exit_usage();
	env->mlx_ptr = NULL;
	env->img_ptr = NULL;
	env->img_str = NULL;
	env->win_ptr = NULL;
	setup_window(env);
	env->camera = init_camera(env);
	if (env->chx == 1)
		env->scene = create_scene_xml(env, fd);
	else
		env->scene = create_scene(env, fd);
	return (env);
}
