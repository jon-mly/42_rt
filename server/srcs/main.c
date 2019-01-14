/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:44 by jmlynarc          #+#    #+#             */
/*   Updated: 2019/01/13 14:07:23 by guillaume        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	local_client(t_env *e)
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

int		parse_arg(t_env *e, char *av, char *av2)
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

int		choose_rt_or_xml(char *av)
{
	char		**tab;
	int			chx;

	chx = 0;
	tab = ft_strsplit(av, '.');
	if (!(ft_strequ(tab[1], "xml") || ft_strequ(tab[1], "rt")))
		ft_error("Bad extension -> .rt or .xml only");
	else if (ft_strequ(tab[1], "xml"))
		chx = 1;
	else
		chx = 0;
	return (chx);
}

int				main(int ac, char **av)
{
	t_g_env	*g_env;

	if (!(g_env = init_gtk_env(ac, av)))
	{
		ft_putendl("erreur d'initialisation de gtk");
		return (EXIT_FAILURE);
	}
	gtk_widget_show_all(g_env->window);
	gtk_main();
	return (0);
}
