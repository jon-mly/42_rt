/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmajstru <gmajstru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 19:25:37 by gmajstru          #+#    #+#             */
/*   Updated: 2019/01/25 20:10:53 by gmajstru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_interface.h"

t_settings	*init_settings(void)
{
	t_settings	*settings;

	settings = NULL;
	if (!(settings = (t_settings*)malloc(sizeof(t_settings))))
	{
		ft_putendl("settings malloc failure !");
		return (settings);
	}
	settings->depth = 0;
	settings->antialiasing = 0;
	settings->is_blur_shadows = FALSE;
	settings->light_spread = 0;
	settings->light_sep = 0;
	settings->is_gl_enabled = FALSE;
	settings->gl_sampling = 0;
	settings->scene_file = NULL;
	return (settings);
}

t_iface		*init_interface(t_g_env *gtk_env)
{
	t_iface		*iface;

	iface = NULL;
	if (!(iface = (t_iface*)malloc(sizeof(t_iface))) ||
		!(iface->labels = init_labels()) ||
		!(iface->window = new_window("RT_prefs", 400, 400)) ||
		!(iface->i_container = new_grid_layout(iface->window, 1, 1)))
	{
		ft_putendl("something went wrong in interface initialization...");
		return (iface);
	}
	iface_widgets_init(iface);
	set_widgets_in_grid(iface);
	g_signal_connect(GTK_WIDGET(iface->window), "destroy",
		G_CALLBACK(gtk_deinit_exit), NULL);
	g_signal_connect(GTK_WIDGET(iface->i_launch_b), "clicked",
		G_CALLBACK(launch_rt), NULL);
	g_signal_connect(GTK_WIDGET(iface->i_exit_b), "clicked",
		G_CALLBACK(gtk_deinit_exit), NULL);
	return (iface);
}

t_g_env		*init_gtk_env(int ac, char **av)
{
	t_g_env	*g;

	g = NULL;
	if (!(g = (t_g_env*)malloc(sizeof(t_g_env))))
	{
		ft_putendl("gtk env malloc error");
		return (g);
	}
	gtk_init(&ac, &av);
	g->datas.ac = ac;
	g->datas.av = av;
	if (!(g->iface = init_interface(g)))
	{
		ft_putendl("interface init error");
		return (NULL);
	}
	if (!(g->rt_settings = init_settings()))
	{
		ft_putendl("settings init error");
		return (NULL);
	}
	return (g);
}
