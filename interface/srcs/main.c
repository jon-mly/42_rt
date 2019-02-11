/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 16:26:13 by gmajstru          #+#    #+#             */
/*   Updated: 2019/02/11 15:31:06 by guillaume        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_interface.h"

int	main(int ac, char **av)
{
	gtk_init(&ac, &av);
	t_settings *rt_set = init_settings();
	if (!rt_set)
	{
		ft_putendl("settings error");
		return (EXIT_FAILURE);
	}

	GtkWidget	*window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "RT_SETTINGS");
	g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	//creating the grid that will contain all the widgets
	GtkWidget	*grid_widget = gtk_grid_new();
	gtk_grid_set_column_homogeneous(GTK_GRID(grid_widget), TRUE);
	gtk_grid_set_row_homogeneous(GTK_GRID(grid_widget), TRUE);
	gtk_container_set_border_width(GTK_CONTAINER(grid_widget), 10);

	GtkWidget	*master_grid = gtk_grid_new();
	gtk_grid_set_column_homogeneous(GTK_GRID(master_grid), TRUE);
	gtk_grid_set_row_homogeneous(GTK_GRID(master_grid), FALSE);


	GtkWidget	*graph_frame = gtk_frame_new("Graphics settings");
	gtk_container_set_border_width(GTK_CONTAINER(graph_frame), 10);
	GtkWidget	*iface_w[17];
	iface_w[0] = gtk_label_new("Max_depth");
	gtk_grid_attach(GTK_GRID(grid_widget), GTK_WIDGET(iface_w[0]), 0, 0, 1, 1);

	iface_w[1] = gtk_label_new("Antialiasing");
	gtk_grid_attach(GTK_GRID(grid_widget), GTK_WIDGET(iface_w[1]), 0, 1, 1, 1);

	iface_w[2] = gtk_label_new("Enable / Disable blur shadows");
	gtk_grid_attach(GTK_GRID(grid_widget), GTK_WIDGET(iface_w[2]), 0, 2, 1, 1);
	
	iface_w[3] = gtk_label_new("light_spread");
	gtk_grid_attach(GTK_GRID(grid_widget), GTK_WIDGET(iface_w[3]), 0, 3, 1, 1);
	
	iface_w[4] = gtk_label_new("light_sep");
	gtk_grid_attach(GTK_GRID(grid_widget), GTK_WIDGET(iface_w[4]), 0, 4, 1, 1);
	
	iface_w[5] = gtk_label_new("Enable/Disable Gl_sampling");
	gtk_grid_attach(GTK_GRID(grid_widget), GTK_WIDGET(iface_w[5]), 0, 5, 1, 1);
	
	iface_w[6] = gtk_label_new("Gl_sampling");
	gtk_grid_attach(GTK_GRID(grid_widget), GTK_WIDGET(iface_w[6]), 0, 6, 1, 1);
	
	iface_w[7] = gtk_label_new("Choose scene file (*.rt / *.xml)");
	gtk_grid_attach(GTK_GRID(grid_widget), GTK_WIDGET(iface_w[7]), 0, 7, 1, 1);

	//creating all widgets of the interface
	//GtkWidget	*iface_w[9];
	iface_w[8] = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 10, 1);
	gtk_range_set_value(GTK_RANGE(iface_w[8]), rt_set->depth);
	g_signal_connect(G_OBJECT(iface_w[8]), "value-changed", G_CALLBACK(update_depth), (t_settings*)rt_set);
	gtk_grid_attach(GTK_GRID(grid_widget), GTK_WIDGET(iface_w[8]), 1, 0, 1, 1);

	iface_w[9] = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 4, 1);
	gtk_range_set_value(GTK_RANGE(iface_w[9]), rt_set->antialiasing);
	g_signal_connect(G_OBJECT(iface_w[9]), "value-changed", G_CALLBACK(update_antialiasing), (t_settings*)rt_set);
	gtk_grid_attach(GTK_GRID(grid_widget), GTK_WIDGET(iface_w[9]), 1, 1, 1, 1);

	iface_w[10] = gtk_check_button_new();
	g_signal_connect(G_OBJECT(iface_w[10]), "toggled", G_CALLBACK(blur_shadows_e_d), iface_w);
	g_signal_connect(G_OBJECT(iface_w[10]), "toggled", G_CALLBACK(update_blursh), (t_settings*)rt_set);
	gtk_grid_attach(GTK_GRID(grid_widget), GTK_WIDGET(iface_w[10]), 1, 2, 1, 1);

	iface_w[11] = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 3, 1);
	gtk_widget_set_sensitive(GTK_WIDGET(iface_w[11]), FALSE);
	gtk_range_set_value(GTK_RANGE(iface_w[11]), rt_set->light_spread);
	g_signal_connect(G_OBJECT(iface_w[11]), "value-changed", G_CALLBACK(update_lightspread), (t_settings*)rt_set);
	gtk_grid_attach(GTK_GRID(grid_widget), GTK_WIDGET(iface_w[11]), 1, 3, 1, 1);

	iface_w[12] = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 3, 1);
	gtk_widget_set_sensitive(GTK_WIDGET(iface_w[12]), FALSE);
	gtk_range_set_value(GTK_RANGE(iface_w[12]), rt_set->light_sep);
	g_signal_connect(G_OBJECT(iface_w[12]), "value-changed", G_CALLBACK(update_lightsep), (t_settings*)rt_set);
	gtk_grid_attach(GTK_GRID(grid_widget), GTK_WIDGET(iface_w[12]), 1, 4, 1, 1);

	iface_w[13] = gtk_check_button_new();
	g_signal_connect(G_OBJECT(iface_w[13]), "toggled", G_CALLBACK(gl_sampling_e_d), iface_w);
	g_signal_connect(G_OBJECT(iface_w[13]), "toggled", G_CALLBACK(update_gl_enable), (t_settings*)rt_set);
	gtk_grid_attach(GTK_GRID(grid_widget), GTK_WIDGET(iface_w[13]), 1, 5, 1, 1);

	iface_w[14] = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 20, 500, 10);
	gtk_widget_set_sensitive(GTK_WIDGET(iface_w[14]), FALSE);
	gtk_range_set_value(GTK_RANGE(iface_w[14]), rt_set->gl_sampling);
	g_signal_connect(G_OBJECT(iface_w[14]), "value-changed", G_CALLBACK(update_glsampling), (t_settings*)rt_set);
	gtk_grid_attach(GTK_GRID(grid_widget), GTK_WIDGET(iface_w[14]), 1, 6, 1, 1);

	iface_w[15] = gtk_button_new_with_label("select a scene file");
	g_signal_connect(G_OBJECT(iface_w[15]), "clicked", G_CALLBACK(select_file), (t_settings*)rt_set);
	gtk_grid_attach(GTK_GRID(grid_widget), GTK_WIDGET(iface_w[15]), 1, 7, 1, 1);

	iface_w[16] = gtk_button_new_with_label("Launch RT");
	g_signal_connect(G_OBJECT(iface_w[16]), "clicked", G_CALLBACK(launch_rt), (t_settings*)rt_set);

	gtk_container_add(GTK_CONTAINER(graph_frame), GTK_WIDGET(grid_widget));

// WINDOW RENDERING PART
	GtkWidget	*w_size_frame = gtk_frame_new("Image rendering size");
	gtk_container_set_border_width(GTK_CONTAINER(w_size_frame), 10);
	GtkWidget	*w_size_grid = gtk_grid_new();
	gtk_grid_set_column_homogeneous(GTK_GRID(w_size_grid), TRUE);
	gtk_grid_set_row_homogeneous(GTK_GRID(w_size_grid), TRUE);
	gtk_container_set_border_width(GTK_CONTAINER(w_size_grid), 10);
	GtkWidget	*size_buttons[3];

	size_buttons[0] = gtk_radio_button_new_with_label(NULL, "900 x 600");
	size_buttons[1] = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(size_buttons[0])), "1350 x 900");
	size_buttons[2] = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(size_buttons[0])), "2025 x 1350");
	gtk_grid_attach(GTK_GRID(w_size_grid), GTK_WIDGET(size_buttons[0]), 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(w_size_grid), GTK_WIDGET(size_buttons[1]), 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(w_size_grid), GTK_WIDGET(size_buttons[2]), 0, 2, 1, 1);
	GSList *rb = gtk_radio_button_get_group(GTK_RADIO_BUTTON(size_buttons[0]));

	while (rb)
	{
		g_signal_connect(G_OBJECT(rb->data), "toggled", G_CALLBACK(update_render_size), (t_settings*)rt_set);
		rb = rb->next;
	}
	gtk_container_add(GTK_CONTAINER(w_size_frame), GTK_WIDGET(w_size_grid));


// SERVER PART
	GtkWidget	*server_frame = gtk_frame_new("Server settings");
	gtk_container_set_border_width(GTK_CONTAINER(server_frame), 10);
	GtkWidget	*server_grid = gtk_grid_new();
	gtk_grid_set_column_homogeneous(GTK_GRID(server_grid), TRUE);
	gtk_grid_set_row_homogeneous(GTK_GRID(server_grid), TRUE);
	gtk_container_set_border_width(GTK_CONTAINER(server_grid), 10);
	GtkWidget	*server_w[2];
	server_w[0] = gtk_label_new("Enter the desired port to connect");
	server_w[1] = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(server_grid), GTK_WIDGET(server_w[0]), 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(server_grid), GTK_WIDGET(server_w[1]), 1, 0, 1, 1);
	g_signal_connect(G_OBJECT(server_w[1]), "changed", G_CALLBACK(update_port), (t_settings*)rt_set);
	gtk_container_add(GTK_CONTAINER(server_frame), GTK_WIDGET(server_grid));

	gtk_grid_attach(GTK_GRID(master_grid), GTK_WIDGET(w_size_frame), 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(master_grid), GTK_WIDGET(graph_frame), 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(master_grid), GTK_WIDGET(server_frame), 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(master_grid), GTK_WIDGET(iface_w[16]), 0, 3, 1, 1);

	gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(master_grid));
	gtk_widget_show_all(GTK_WIDGET(window));
	gtk_main();
	return (0);
}
