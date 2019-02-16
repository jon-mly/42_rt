/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:05:50 by aabelque          #+#    #+#             */
/*   Updated: 2019/02/16 17:01:22 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static	void	setup_window(t_env *env)
{
	int		bpp;
	int		s_l;
	int		endian;

	env->mlx_ptr = mlx_init();
	env->win_ptr = mlx_new_window(env->mlx_ptr, DEFAULT_SIZE, DEFAULT_SIZE,
			"Client RT");
	env->win_height = DEFAULT_SIZE;
	env->win_width = DEFAULT_SIZE;
	if (env->mlx_ptr == NULL || env->win_ptr == NULL)
		exit_error(env);
	env->img_ptr = mlx_new_image(env->mlx_ptr, env->win_width, env->win_height);
	env->img_width = DEFAULT_SIZE;
	env->img_height = DEFAULT_SIZE;
	env->img_str = mlx_get_data_addr(env->img_ptr, &bpp, &s_l, &endian);
	if (env->img_ptr == NULL || env->img_str == NULL)
		exit_error(env);
	env->line_size = s_l / 4;
	env->bpp = bpp;
	env->endian = endian;
}

void			init_env2(t_env *env)
{
	env->win_height = DEFAULT_SIZE;
	env->win_width = DEFAULT_SIZE;
	env->img_width = DEFAULT_SIZE;
	env->img_height = DEFAULT_SIZE;
	env->mlx_ptr = NULL;
	env->img_ptr = NULL;
	env->img_str = NULL;
	env->win_ptr = NULL;
	setup_window(env);
	env->camera = init_camera(env);
}
