/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmajstru <gmajstru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 13:58:36 by guillaume         #+#    #+#             */
/*   Updated: 2019/01/25 20:04:11 by gmajstru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_interface.h"

void	gtk_deinit_exit(GtkButton *exit_b, gpointer g_datas)
{
	t_g_env *datas;

	datas = (t_g_env*)g_datas;
	if (datas)
	{
		if (datas->iface)
			if (datas->iface->i_container)
				gtk_widget_destroy(datas->iface->i_container);
		free(datas->iface);
	}
	free(datas);
	gtk_main_quit();
}

void	launch_rt(GtkButton *button, gpointer user_data)
{
	if (execlp("./rt", "rt",
		"/Users/gmajstru/Google Drive/42/PERSO/RT_/rt_scenes/bump.rt", "-p",
				"4242", (char *)NULL) == -1)
	{
		ft_putendl("Error function execlp()");
		exit(EXIT_FAILURE);
	}
}
