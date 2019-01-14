/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 13:58:36 by guillaume         #+#    #+#             */
/*   Updated: 2019/01/13 14:16:42 by guillaume        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_iface	*init_interface()
{
	t_iface	*iface;

	iface = NULL;
	if (!(iface = (t_iface*)malloc(sizeof(t_iface))))
	{
		ft_putendl("interface malloc error");
		return (iface);
	}
	iface->i_container = gtk_vbox_new(FALSE, 0);
	iface->i_launch_b = gtk_button_new_with_label("Launch raytracing");
	iface->i_exit_b = gtk_button_new_with_label("Exit");
	gtk_container_add(GTK_CONTAINER(iface->i_container), iface->i_launch_b);
	gtk_container_add(GTK_CONTAINER(iface->i_container), iface->i_exit_b);
/* 	gtk_box_pack_start(GTK_BOX(iface->i_container), iface->i_launch_b, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(iface->i_container), iface->i_exit_b, FALSE, FALSE, 0); */
	return (iface);
}

t_g_env *init_gtk_env(int ac, char **av)
{
	t_g_env	*g;

	g = NULL;
	if (!(g = (t_g_env*)malloc(sizeof(t_g_env))))
	{
		ft_putendl("gtk env malloc error");
		return (g);
	}
	gtk_init(&ac, &av);
	g->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g->datas.ac = ac;
	g->datas.av = av;
	if (!(g->iface = init_interface()))
	{
		ft_putendl("interface init error");
		return (NULL);
	}
	gtk_container_add(GTK_CONTAINER(g->window), g->iface->i_container);
	g_signal_connect(GTK_WIDGET(g->window), "destroy", G_CALLBACK(gtk_deinit_exit), NULL);
	g_signal_connect(GTK_WIDGET(g->iface->i_launch_b), "clicked", G_CALLBACK(launch_rt), (t_data*)&g->datas);
	g_signal_connect(GTK_WIDGET(g->iface->i_exit_b), "clicked", G_CALLBACK(gtk_deinit_exit), NULL);
	return (g);
}

void	gtk_deinit_exit(GtkButton* exit_b, gpointer g_datas)
{
	t_g_env *datas = (t_g_env*)g_datas;

	if (datas)
	{
		if (datas->iface)
			if (datas->iface->i_container)
				gtk_widget_destroy(datas->iface->i_container);
		free(datas->iface);
		if (datas->window)
			gtk_widget_destroy(datas->window);
	}
	free(datas);
	gtk_main_quit();
}

void			launch_rt(GtkButton *button, gpointer user_data)
{
	t_env		*env;
	int			chx;
	int			ac;
	char		**av;
	t_data 		d;

	d = *((t_data*)user_data);
	ac = d.ac;
	av = d.av;
	printf("ac: %d\n", d.ac);
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
}
