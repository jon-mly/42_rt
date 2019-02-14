/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 19:25:37 by gmajstru          #+#    #+#             */
/*   Updated: 2019/02/14 23:40:14 by guillaume        ###   ########.fr       */
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
	settings->err = 1;
	settings->depth = 1;
	settings->antialiasing = 1;
	settings->is_blur_shadows = FALSE;
	settings->light_spread = 1;
	settings->light_sep = 1;
	settings->is_gl_enabled = FALSE;
	settings->gl_sampling = 20;
	settings->scene_file = NULL;
	settings->port = 0;
	settings->render_w = 900;
	settings->render_h = 600;
	return (settings);
}

GtkWidget	*create_window(const gchar *title)
{
	GtkWidget	*new_window;

	new_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(new_window), title);
	g_signal_connect(GTK_WINDOW(new_window), "destroy",
		G_CALLBACK(gtk_main_quit), NULL);
	return (new_window);
}

GtkWidget	*create_grid(gboolean c_hom, gboolean r_hom, guint border_width)
{
	GtkWidget	*new_grid;

	new_grid = gtk_grid_new();
	gtk_grid_set_column_homogeneous(GTK_GRID(new_grid), c_hom);
	gtk_grid_set_row_homogeneous(GTK_GRID(new_grid), r_hom);
	gtk_container_set_border_width(GTK_CONTAINER(new_grid), border_width);
	return (new_grid);
}

GtkWidget	*create_frame(const gchar *title, guint border_width)
{
	GtkWidget	*new_frame;

	new_frame = gtk_frame_new(title);
	gtk_container_set_border_width(GTK_CONTAINER(new_frame), border_width);
	return (new_frame);
}

void		init_iface_w(GtkWidget **iface_w)
{
	iface_w[0] = gtk_label_new("Max_depth");
	iface_w[1] = gtk_label_new("Antialiasing");
	iface_w[2] = gtk_label_new("Enable / Disable blur shadows");
	iface_w[3] = gtk_label_new("light_spread");
	iface_w[4] = gtk_label_new("light_sep");
	iface_w[5] = gtk_label_new("Enable/Disable Gl_sampling");
	iface_w[6] = gtk_label_new("Gl_sampling");
	iface_w[7] = gtk_label_new("Choose scene file (*.rt / *.xml)");
	iface_w[8] = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
		1, 10, 1);
	iface_w[9] = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 4, 1);
	iface_w[10] = gtk_check_button_new();
	iface_w[11] = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
		1, 3, 1);
	iface_w[12] = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
		1, 3, 1);
	iface_w[13] = gtk_check_button_new();
	iface_w[14] = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
		20, 500, 10);
	iface_w[15] = gtk_button_new_with_label("select a scene file");
	iface_w[16] = gtk_button_new_with_label("Launch RT");
	gtk_widget_set_sensitive(GTK_WIDGET(iface_w[11]), FALSE);
	gtk_widget_set_sensitive(GTK_WIDGET(iface_w[12]), FALSE);
	gtk_widget_set_sensitive(GTK_WIDGET(iface_w[14]), FALSE);
}
