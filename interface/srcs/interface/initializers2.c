/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 23:37:52 by guillaume         #+#    #+#             */
/*   Updated: 2019/02/15 14:24:09 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_interface.h"

void	attach_widgets_grid(GtkWidget **lbls, GtkWidget *grid, guint size)
{
	guint	i;

	i = -1;
	while (++i < size)
	{
		(i <= 7) ?
			gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(lbls[i]), 0, i, 1, 1) :
			gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(lbls[i]), 1, i - 8, 1,
					1);
	}
}

void	init_range_values(GtkWidget **iface_w, t_settings *rt_set)
{
	gtk_range_set_value(GTK_RANGE(iface_w[8]), rt_set->depth);
	gtk_range_set_value(GTK_RANGE(iface_w[9]), rt_set->antialiasing);
	gtk_range_set_value(GTK_RANGE(iface_w[11]), rt_set->light_spread);
	gtk_range_set_value(GTK_RANGE(iface_w[12]), rt_set->light_sep);
	gtk_range_set_value(GTK_RANGE(iface_w[14]), rt_set->gl_sampling);
}

void	connect_widgets_signals(GtkWidget **iface_w, t_settings *rt_set)
{
	g_signal_connect(G_OBJECT(iface_w[8]), "value-changed",
			G_CALLBACK(update_depth), (t_settings*)rt_set);
	g_signal_connect(G_OBJECT(iface_w[9]), "value-changed",
			G_CALLBACK(update_antialiasing), (t_settings*)rt_set);
	g_signal_connect(G_OBJECT(iface_w[10]), "toggled",
			G_CALLBACK(blur_shadows_e_d), iface_w);
	g_signal_connect(G_OBJECT(iface_w[10]), "toggled",
			G_CALLBACK(update_blursh), (t_settings*)rt_set);
	g_signal_connect(G_OBJECT(iface_w[11]), "value-changed",
			G_CALLBACK(update_lightspread), (t_settings*)rt_set);
	g_signal_connect(G_OBJECT(iface_w[12]), "value-changed",
			G_CALLBACK(update_lightsep), (t_settings*)rt_set);
	g_signal_connect(G_OBJECT(iface_w[13]), "toggled",
			G_CALLBACK(gl_sampling_e_d), iface_w);
	g_signal_connect(G_OBJECT(iface_w[13]), "toggled",
			G_CALLBACK(update_gl_enable), (t_settings*)rt_set);
	g_signal_connect(G_OBJECT(iface_w[14]), "value-changed",
			G_CALLBACK(update_glsampling), (t_settings*)rt_set);
	g_signal_connect(G_OBJECT(iface_w[15]), "clicked",
			G_CALLBACK(select_file), (t_settings*)rt_set);
	g_signal_connect(G_OBJECT(iface_w[16]), "clicked",
			G_CALLBACK(launch_rt), (t_settings*)rt_set);
}

void	init_size_w(GtkWidget **sz_btn, GtkWidget *w_size_grid,
		t_settings *rt_set)
{
	GSList	*rb;

	rb = NULL;
	sz_btn[0] = gtk_radio_button_new_with_label(NULL, "900 x 600");
	sz_btn[1] = gtk_radio_button_new_with_label(
			gtk_radio_button_get_group(
				GTK_RADIO_BUTTON(sz_btn[0])), "1350 x 900");
	sz_btn[2] = gtk_radio_button_new_with_label(
			gtk_radio_button_get_group(
				GTK_RADIO_BUTTON(sz_btn[0])), "2025 x 1350");
	gtk_grid_attach(GTK_GRID(w_size_grid), GTK_WIDGET(sz_btn[0]), 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(w_size_grid), GTK_WIDGET(sz_btn[1]), 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(w_size_grid), GTK_WIDGET(sz_btn[2]), 0, 2, 1, 1);
	rb = gtk_radio_button_get_group(GTK_RADIO_BUTTON(sz_btn[0]));
	while (rb)
	{
		g_signal_connect(G_OBJECT(rb->data), "toggled",
				G_CALLBACK(update_render_size), (t_settings*)rt_set);
		rb = rb->next;
	}
	g_slist_free(rb);
}

void	init_server_w(GtkWidget **server_w, GtkWidget *server_grid,
		t_settings *rt_set)
{
	server_w[0] = gtk_label_new("Enter the desired port to connect");
	server_w[1] = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(server_grid), GTK_WIDGET(server_w[0]), 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(server_grid), GTK_WIDGET(server_w[1]), 1, 0, 1, 1);
	g_signal_connect(G_OBJECT(server_w[1]), "changed",
			G_CALLBACK(update_port), (t_settings*)rt_set);
}
