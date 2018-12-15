/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:40:56 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/15 19:14:41 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static	int		parse_arg(t_env *e, char *av, char *av2)
{
	if (ft_strequ(av, "-p"))
	{
		if (ft_atoi(av2) >= 0 && ft_atoi(av2) <= 1024)
			exit_usage();
		else
			e->srv.port = ft_atoi(av2);
	}
	return (1);
}

int			main(int ac, char **av)
{
	t_env	*env;

	if (ac != 4)
		exit_usage2();
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		exit(EXIT_FAILURE);
	parse_arg(env, av[2], av[3]);
	env = init_env2();
	init_env_client(env, av[1]);
	create_client(env);
	write(1, "L\n", 2);
	recv_client(env);
	write(1, "E\n", 2);
	//set_opencl_env(&env->opcl);
	//opencl_init(&env->opcl, env);
//	opencl_draw(&env->opcl, env);
//	if ((mlx_put_image_to_window(env->mlx_ptr, env->win_ptr,
//					env->img_ptr, 0, 0)) == -1)
//		ft_putendl("Failed to put image to window");
//	mlx_hook(env->win_ptr, 2, 0, handle_key_event, (void*)env);
//	mlx_hook(env->win_ptr, 17, 0, exit_properly, (void*)env);
//	mlx_loop_hook(env->mlx_ptr, expose_event, (void*)env);
//	mlx_loop(env->mlx_ptr);
	return (0);
}
