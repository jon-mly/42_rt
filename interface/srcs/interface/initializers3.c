/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 23:38:45 by guillaume         #+#    #+#             */
/*   Updated: 2019/02/15 15:49:07 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_interface.h"

t_inter	new_interface(void)
{
	t_inter	inter;

	if (!(inter.rt_set = init_settings()))
	{
		ft_putendl("settings error");
		exit(1);
	}
	inter.window = create_window("RT_Settings");
	inter.grid_widget = create_grid(TRUE, TRUE, 10);
	inter.master_grid = create_grid(TRUE, FALSE, 0);
	inter.graph_frame = create_frame("Graphics Settings", 10);
	inter.w_size_frame = create_frame("Image Rendering Size", 10);
	inter.w_size_grid = create_grid(TRUE, TRUE, 10);
	inter.server_frame = create_frame("Server settings", 10);
	inter.server_grid = create_grid(TRUE, TRUE, 10);
	return (inter);
}

void	setup_grids(t_inter *inter)
{
	gtk_container_add(GTK_CONTAINER(inter->graph_frame),
			GTK_WIDGET(inter->grid_widget));
	gtk_container_add(GTK_CONTAINER(inter->w_size_frame),
			GTK_WIDGET(inter->w_size_grid));
	gtk_container_add(GTK_CONTAINER(inter->server_frame),
			GTK_WIDGET(inter->server_grid));
	gtk_grid_attach(GTK_GRID(inter->master_grid),
			GTK_WIDGET(inter->w_size_frame), 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(inter->master_grid),
			GTK_WIDGET(inter->graph_frame), 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(inter->master_grid),
			GTK_WIDGET(inter->server_frame), 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(inter->master_grid),
			GTK_WIDGET(inter->iface_w[16]), 0, 3, 1, 1);
	gtk_container_add(GTK_CONTAINER(inter->window),
			GTK_WIDGET(inter->master_grid));
}

void	run_dialog(t_settings *settings)
{
	GtkWidget		*dialog;
	GtkFileChooser	*chooser;
	char			*filename;
	gint			res;

	dialog = gtk_file_chooser_dialog_new("Open File",
			NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
			"_Cancel", GTK_RESPONSE_CANCEL, "_Open",
			GTK_RESPONSE_ACCEPT, NULL);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),
											"./rt_scenes/");
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		chooser = GTK_FILE_CHOOSER(dialog);
		filename = gtk_file_chooser_get_filename(chooser);
		settings->scene_file = ft_strdup(filename);
		g_free(filename);
	}
	gtk_widget_destroy(dialog);
}
