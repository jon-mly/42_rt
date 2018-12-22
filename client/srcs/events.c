/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:31 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/08/07 11:21:20 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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
