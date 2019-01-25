/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmajstru <gmajstru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 16:26:13 by gmajstru          #+#    #+#             */
/*   Updated: 2019/01/25 17:14:26 by gmajstru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_interface.h"

int	main(int ac, char **av)
{
	t_g_env	*g_env;

	if (!(g_env = init_gtk_env(ac, av)))
	{
		ft_putendl("erreur d'initialisation de gtk");
		return (EXIT_FAILURE);
	}
	gtk_widget_show_all(g_env->iface->window);
	gtk_main();
	return (0);
}
