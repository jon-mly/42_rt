/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmajstru <gmajstru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 19:24:26 by gmajstru          #+#    #+#             */
/*   Updated: 2019/01/25 20:06:20 by gmajstru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_interface.h"

GtkWidget	*new_window(const gchar *title, gint width, gint height)
{
	GtkWidget	*new_window;

	new_window = NULL;
	if (!(new_window = gtk_window_new(GTK_WINDOW_TOPLEVEL)))
	{
		ft_putendl("error creating the window");
		return (new_window);
	}
	gtk_window_set_default_size(GTK_WINDOW(new_window), width, height);
	gtk_window_set_title(GTK_WINDOW(new_window), title);
	return (new_window);
}

GtkWidget	*new_grid_layout(GtkWidget *container_to_add,
	gboolean homogeneous_col, gboolean homogeneous_row)
{
	GtkWidget	*new_grid;

	new_grid = NULL;
	if (!(new_grid = gtk_grid_new()))
		return (new_grid);
	gtk_container_add(GTK_CONTAINER(container_to_add), new_grid);
	gtk_grid_set_column_homogeneous(GTK_GRID(new_grid), homogeneous_col);
	gtk_grid_set_row_homogeneous(GTK_GRID(new_grid), homogeneous_row);
	return (new_grid);
}
