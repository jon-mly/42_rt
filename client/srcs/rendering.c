/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 16:50:35 by aabelque          #+#    #+#             */
/*   Updated: 2019/02/16 16:50:38 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			await_data(t_env *env)
{
	env->srv.cl_state = WAIT_DATA;
	recv_obj_light(env);
}

static void		update_window2(t_env *env)
{
	int		bpp;
	int		s_l;
	int		endian;

	env->img_str = mlx_get_data_addr(env->img_ptr, &bpp, &s_l, &endian);
	if (env->img_ptr == NULL || env->img_str == NULL)
		exit_error(env);
	env->line_size = s_l / 4;
	env->bpp = bpp;
	env->endian = endian;
	env->camera.horizontal_step = env->camera.width / (double)(env->win_width);
	env->camera.vertical_step = env->camera.height / (double)(env->win_height);
	mlx_hook(env->win_ptr, 2, 0, handle_key_event, (void*)env);
	mlx_hook(env->win_ptr, 17, 0, exit_properly, (void*)env);
	mlx_loop_hook(env->mlx_ptr, expose_event, (void*)env);
	set_opencl_env(env, &env->opcl);
}

static	void	update_window(t_env *env)
{
	mlx_destroy_image(env->mlx_ptr, env->img_ptr);
	mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	env->win_width = env->scene.sett.render_w;
	env->win_height = env->scene.sett.render_h;
	env->win_ptr = mlx_new_window(env->mlx_ptr, env->win_width,
		env->win_height, "Client RT");
	if (env->mlx_ptr == NULL || env->win_ptr == NULL)
		exit_error(env);
	env->img_width = env->win_width;
	env->img_height = env->win_height;
	env->img_ptr = mlx_new_image(env->mlx_ptr, env->img_width,
		env->img_height);
	update_window2(env);
}

void			perform_rendering(t_env *env)
{
	env->srv.cl_state = RENDERING;
	update_window(env);
	opencl_init(&env->opcl, env);
	opencl_draw(&env->opcl, env);
}

void			send_rendering(t_env *env)
{
	int		err;
	int		size;
	char	*tmp;

	tmp = env->img_str;
	size = env->win_width * env->win_height * 4 * sizeof(char);
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
