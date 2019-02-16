/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 16:49:44 by aabelque          #+#    #+#             */
/*   Updated: 2019/02/16 17:01:21 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static	int		parse_arg(t_env *e, char *av, char *av2)
{
	if (ft_strequ(av, "-p"))
	{
		if (ft_atoi(av2) >= 0 && ft_atoi(av2) <= 1024)
			exit_usage2();
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
	init_env2(env);
	init_env_client(env, av[1]);
	create_client(env);
	loop_client_lifecycle(env);
	mlx_hook(env->win_ptr, 2, 0, handle_key_event, (void*)env);
	mlx_hook(env->win_ptr, 17, 0, exit_properly, (void*)env);
	mlx_loop_hook(env->mlx_ptr, expose_event, (void*)env);
	mlx_loop(env->mlx_ptr);
	return (0);
}
