/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 10:24:58 by aabelque          #+#    #+#             */
/*   Updated: 2019/02/14 23:44:28 by guillaume        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void			local_client(t_env *e)
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

static	int		parse_arg2(t_env *e, char **av)
{
	if ((ft_atoi(av[4]) >= 1 && ft_atoi(av[4]) <= 10) &&
			(ft_atoi(av[5]) >= 0 && ft_atoi(av[5]) <= 4) &&
			(ft_atoi(av[6]) >= 0 && ft_atoi(av[6]) <= 1) &&
			(ft_atoi(av[7]) >= 0 && ft_atoi(av[7]) <= 3) &&
			(ft_atoi(av[8]) >= 0 && ft_atoi(av[8]) <= 4) &&
			(ft_atoi(av[9]) >= 0 && ft_atoi(av[9]) <= 1) &&
			(ft_atoi(av[10]) >= 0 && ft_atoi(av[10]) <= 500) &&
			((ft_atoi(av[11]) == 900 && ft_atoi(av[12]) == 600)
			|| (ft_atoi(av[11]) == 1350 && ft_atoi(av[12]) == 900)
			|| (ft_atoi(av[11]) == 2025 && ft_atoi(av[12]) == 1350)))
	{
		e->scene.sett.depth = (unsigned int)ft_atoi(av[4]);
		e->scene.sett.aliasing = (unsigned int)ft_atoi(av[5]);
		e->scene.sett.bshadows = (unsigned int)ft_atoi(av[6]);
		e->scene.sett.spread = (unsigned int)ft_atoi(av[7]);
		e->scene.sett.sep = (unsigned int)ft_atoi(av[8]);
		e->scene.sett.gl_enabled = (unsigned int)ft_atoi(av[9]);
		e->scene.sett.gl_sampling = (unsigned int)ft_atoi(av[10]);
		e->scene.sett.render_w = (unsigned int)ft_atoi(av[11]);
		e->scene.sett.render_h = (unsigned int)ft_atoi(av[12]);
	}
	else
		return (1);
	return (0);
}

int				parse_arg(t_env *e, char **av)
{
	if (ft_strequ(av[2], "-p"))
	{
		if (has_alpha(av[3]) || (ft_atoi(av[3]) <= 0
					|| ft_atoi(av[3]) <= 1024) || ft_atoi(av[3]) > 65535)
			exit_usage();
		else
			e->srv.port = ft_atoi(av[3]);
	}
	if ((has_alpha(av[4]) || has_alpha(av[5]) || has_alpha(av[6])
				|| has_alpha(av[7]) || has_alpha(av[8]) || has_alpha(av[9])
				|| has_alpha(av[10]) || has_alpha(av[11])
				|| has_alpha(av[12])) || parse_arg2(e, av) != 0)
		exit_usage();
	return (0);
}

int				choose_rt_or_xml(char *av)
{
	char	**tab;
	int		chx;
	int		i;

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
	t_env	*env;
	int		chx;

	chx = 0;
	(ac != 13) ? exit_usage() : 0;
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		exit(EXIT_FAILURE);
	parse_arg(env, av);
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
