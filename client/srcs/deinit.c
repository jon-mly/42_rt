/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:21 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/12/21 18:37:32 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			ft_error(char *str)
{
	ft_putendl(str);
	exit(EXIT_FAILURE);
}

static void		deinit_scene(t_scene scene)
{
	ft_memdel((void**)(&(scene.objects)));
	ft_memdel((void**)(&(scene.lights)));
}

void			deinit_env(t_env *env)
{
	opencl_free(&env->opcl);
	ft_putendl("Deinit triggered");
	deinit_scene(env->scene);
	ft_putendl("Scene is deinited");
	if (env->img_ptr && env->mlx_ptr)
		mlx_destroy_image(env->mlx_ptr, env->img_ptr);
	if (env->win_ptr && env->mlx_ptr)
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	ft_memdel((void**)(&env));
}
