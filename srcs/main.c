/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:44 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/11/12 13:11:11 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "cu_rt.h"

int				main(int ac, char **av)
{
	t_env		*env;

	if (ac != 2)
		exit_usage();
	env = init_env(av[1]);
	init_gpu(env, &env->gpu);
	malloc_gpu(env, &env->gpu);
	copy_gpu(env, &env->gpu);
	call_kernel(env, &env->gpu);
	//set_opencl_env(&env->opcl);
	//opencl_init(&env->opcl, env);
	//opencl_draw(&env->opcl, env);
	//fill_pixel_value(env, -1, -1, *env->gpu.render_img);
	//printf("render_img: %d\n", *env->gpu.render_img);
	if ((mlx_put_image_to_window(env->mlx_ptr, env->win_ptr,
					env->img_ptr, 0, 0)) == -1)
		ft_putendl("Failed to put image to window");
	mlx_hook(env->win_ptr, 2, 0, handle_key_event, (void*)env);
	mlx_hook(env->win_ptr, 17, 0, exit_properly, (void*)env);
	mlx_loop_hook(env->mlx_ptr, expose_event, (void*)env);
	mlx_loop(env->mlx_ptr);
	return (0);
}
