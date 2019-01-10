/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:44 by jmlynarc          #+#    #+#             */
/*   Updated: 2019/01/10 18:24:49 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
			if ((*tmp >= 'a' && *tmp <= 'z') || (*tmp >= 'A' && *tmp <= 'Z'))
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

static	int		choose_rt_or_xml(char *av)
{
	char		**tab;
	int			chx;
	int			i;

	chx = 0;
	i = -1;
	tab = ft_strsplit(av, '.');
	if (!(ft_strequ(tab[1], "xml") || ft_strequ(tab[1], "rt")))
		ft_error("Bad extension -> .rt or .xml only");
	else if (ft_strequ(tab[1], "xml"))
		chx = 1;
	else
		chx = 0;
	while (i++ < 2)
		ft_memdel((void**)&tab[i]);
	ft_memdel((void**)(&tab));
	return (chx);
}

int				main(int ac, char **av)
{
	t_env		*env;
	int			chx;

	chx = 0;
	(ac != 4) ? exit_usage() : 0;
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		exit(EXIT_FAILURE);
	parse_arg(env, av[2], av[3]);
	env->chx = choose_rt_or_xml(av[1]);
	env = init_env(env, av[1]);
	init_env_server(env);
	create_srv(env);
	if (pthread_create(&env->thr, NULL, waitcl, env))
	{
		ft_putendl("Error function pthread_create()");
		exit(EXIT_FAILURE);
	}
	local_client(env);
	mlx_hook(env->win_ptr, 2, 0, handle_key_event, (void*)env);
	mlx_hook(env->win_ptr, 17, 0, exit_properly, (void*)env);
	mlx_loop_hook(env->mlx_ptr, expose_event, (void*)env);
	mlx_loop(env->mlx_ptr);
	return (0);
}
