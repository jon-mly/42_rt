/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 16:26:13 by gmajstru          #+#    #+#             */
/*   Updated: 2019/02/16 17:18:14 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_interface.h"

static gboolean		check_escape(GtkWidget *widget, GdkEventKey *event,
		gpointer data)
{
	if (event->keyval == GDK_KEY_Escape)
	{
		gtk_main_quit();
		return (TRUE);
	}
	return (FALSE);
}

int					main(int ac, char **av)
{
	t_inter	inter;

	gtk_init(&ac, &av);
	inter = new_interface();
	init_iface_w(inter.iface_w);
	init_range_values(inter.iface_w, inter.rt_set);
	connect_widgets_signals(inter.iface_w, inter.rt_set);
	attach_widgets_grid(inter.iface_w, inter.grid_widget, 16);
	init_size_w(inter.size_buttons, inter.w_size_grid, inter.rt_set);
	init_server_w(inter.server_w, inter.server_grid, inter.rt_set);
	setup_grids(&inter);
	g_signal_connect(G_OBJECT(inter.window), "key_press_event",
		G_CALLBACK(check_escape), NULL);
	gtk_widget_show_all(GTK_WIDGET(inter.window));
	gtk_main();
	return (0);
}
