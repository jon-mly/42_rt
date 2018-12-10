/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:40:56 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/10 18:55:28 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

//int		g_socket_cl;
//int		g_socket;

/*static	void	quit(int sig)
{
	(void)sig;
	close(g_socket_cl);
	close(g_socket);
	exit(EXIT_SUCCESS);
}*/

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
	//env = init_env2();
	init_env_client(env, av[1]);
	create_client(env);
	write(1, "W", 1);
	//signal(SIGTERM, quit);
	recv_client(env);
	set_opencl_env(&env->opcl);
	opencl_init(&env->opcl, env);
	return (0);
}
