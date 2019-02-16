/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmajstru <gmajstru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:31 by jmlynarc          #+#    #+#             */
/*   Updated: 2019/02/16 18:23:33 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			exit_properly(void *param)
{
	t_env	*env;

	env = (t_env*)param;
	exit_normally(env);
	return (0);
}

int			handle_key_event(int key, void *param)
{
	t_env		*env;

	env = (t_env*)param;
	if (key == KEY_ESC)
		exit_normally(env);
	else if (key == KEY_SPACE)
	{
		if (env->srv.state == WAIT_CLIENTS)
		{
			env->srv.state = WAIT_RENDER;
			request_rendering(env);
		}
	}
	return (0);
}

int			expose_event(void *param)
{
	t_env		*env;

	env = (t_env*)param;
	if (env->mlx_ptr && env->win_ptr && env->img_ptr)
		mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);
	return (0);
}
