/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:44 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/12/17 17:06:10 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	void	local_client(t_env *e)
{
	e->child = fork();
	if (e->child == -1)
	{
		ft_putendl("Error function fork()");
		exit(EXIT_FAILURE);
	}
	if (!e->child)
	{
		if (execlp("./rt_client", "rt_client", "127.0.0.1", "-p",
					ft_itoa(e->srv.port), (char *)NULL) == -1)
		{
			ft_putendl("Error function execlp()");
			exit(EXIT_FAILURE);
		}
	}
}

static	int		parse_arg(t_env *e, char *av, char *av2)
{
	char *tmp;

	tmp = av2;
	if (ft_strequ(av, "-p"))
	{
		while (*tmp)
		{
			if (*tmp >= 'a' && *tmp <= 'z')
				exit_usage();
			tmp++;
		}
		if ((ft_atoi(av2) >= 0 && ft_atoi(av2) <= 1024) || ft_atoi(av2) < 0)
			exit_usage();
		else
			e->srv.port = ft_atoi(av2);
	}
	else
		exit_usage();
	return (0);
}

int				main(int ac, char **av)
{
	t_env		*env;
	t_env		data;

	(ac != 4) ? exit_usage() : 0;
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		exit(EXIT_FAILURE);
	parse_arg(env, av[2], av[3]);
	env = init_env(env, av[1]);
	init_env_server(env);
	create_srv(env);
	data = *env;
	if (pthread_create(&env->thr, NULL, waitcl, env))
	{
		ft_putendl("Error function pthread_create()");
		exit(EXIT_FAILURE);
	}
	// local_client(env);
	if ((mlx_put_image_to_window(env->mlx_ptr, env->win_ptr,
					env->img_ptr, 0, 0)) == -1)
		ft_putendl("Failed to put image to window");
	mlx_hook(env->win_ptr, 2, 0, handle_key_event, (void*)env);
	mlx_hook(env->win_ptr, 17, 0, exit_properly, (void*)env);
	mlx_loop_hook(env->mlx_ptr, expose_event, (void*)env);
	mlx_loop(env->mlx_ptr);
	return (0);
}
