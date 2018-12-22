/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:40:56 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/21 18:39:23 by aabelque         ###   ########.fr       */
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

void			*loop_client_lifecycle(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	await_data(env);
	perform_rendering(env);
	send_rendering(env);
	return (NULL);
}

int				main(int ac, char **av)
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
	mlx_hook(env->win_ptr, 2, 0, handle_key_event, (void*)env);
	mlx_hook(env->win_ptr, 17, 0, exit_properly, (void*)env);
	mlx_loop_hook(env->mlx_ptr, expose_event, (void*)env);
	set_opencl_env(&env->opcl);
	if (pthread_create(&(env->thr), NULL, loop_client_lifecycle, env))
		ft_error("Error launching client lifecycle : pthread_create");
	if (pthread_join(env->thr, NULL))
		ft_error("Error launching client lifecycle : pthread_join");
	mlx_loop(env->mlx_ptr);
	return (0);
}
