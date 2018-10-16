/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:44 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/09/07 12:00:28 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	int		parse_arg(char *av)
{
	int			device;

	device = 0;
	device = (ft_strequ(av, "-cpu")) ? 1 : 0;
	if (device == 0)
		device = (ft_strequ(av, "-gpu")) ? 2 : 0;
	if (device == 0)
		exit_usage();
	return (device);
}

int				main(int ac, char **av)
{
	t_env		*env;
	int			device;

	device = 0;
	if (ac != 3)
		exit_usage();
	device = parse_arg(av[1]);
	env = init_env(av[2]);
	(device == 1) ? calculate_scene(env) : (void *)env;
	if (device == 2)
	{
		set_opencl_env(&env->opcl);
		opencl_init(&env->opcl, env);
		opencl_draw(&env->opcl, env);
	}
	if ((mlx_put_image_to_window(env->mlx_ptr, env->win_ptr,
					env->img_ptr, 0, 0)) == -1)
		ft_putendl("Failed to put image to window");
	mlx_hook(env->win_ptr, 2, 0, handle_key_event, (void*)env);
	mlx_hook(env->win_ptr, 17, 0, exit_properly, (void*)env);
	mlx_loop_hook(env->mlx_ptr, expose_event, (void*)env);
	mlx_loop(env->mlx_ptr);
	return (0);
}
