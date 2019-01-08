/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 18:36:01 by aabelque          #+#    #+#             */
/*   Updated: 2019/01/03 17:33:56 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void		await_data(t_env *env)
{
	env->srv.cl_state = WAIT_DATA;
	recv_obj_light(env);
}

void		perform_rendering(t_env *env)
{
	env->srv.cl_state = RENDERING;
	opencl_init(&env->opcl, env);
	opencl_draw(&env->opcl, env);
}

void		send_rendering(t_env *env)
{
	int		err;
	int		size;
	char	*tmp;

	tmp = env->img_str;
	size = WIN_WIDTH * WIN_HEIGHT * 4 * sizeof(char);
	env->srv.cl_state = SENDING;
	if ((mlx_put_image_to_window(env->mlx_ptr, env->win_ptr,
					env->img_ptr, 0, 0)) == -1)
		ft_putendl("Failed to put image to window");
	while (size > 0)
	{
		if ((err = send(env->srv.socket, tmp, (int)fmin(1024, size), 0)) < 0)
			ft_error("send() > send_rendering()");
		size -= err;
		tmp += err;
	}
	ft_putendl("HAS TERMINATED SENDING");
}
