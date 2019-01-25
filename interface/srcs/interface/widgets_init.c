/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widgets_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmajstru <gmajstru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 19:34:38 by gmajstru          #+#    #+#             */
/*   Updated: 2019/01/25 20:23:59 by gmajstru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_interface.h"

t_labels	*init_labels(void)
{
	t_labels	*lab;

	lab = NULL;
	if (!(lab = (t_labels*)malloc(sizeof(t_labels))))
	{
		ft_putendl("label malloc failure");
		return (NULL);
	}
	lab->max_depth = gtk_label_new("Max_depth:");
	lab->antialiasing = gtk_label_new("Antialiasing:");
	lab->blur_shadows = gtk_label_new("Enable/Disable Blur Shadows:");
	lab->light_spread = gtk_label_new("light_spread:");
	lab->light_sep = gtk_label_new("light_sep:");
	lab->gl_enabled = gtk_label_new("Enable/Disable Gl_sampling:");
	lab->gl_sampling = gtk_label_new("gl_sampling:");
	return (lab);
}

void		iface_widgets_init(t_iface *iface)
{
	iface->i_depth = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
		1, 10, 1);
	iface->i_antialiasing = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
		0, 4, 1);
	iface->i_light_spread = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
		1, 3, 1);
	iface->i_light_sep = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
		1, 3, 1);
	iface->i_gl_sampling = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
		20, 50, 10);
	iface->i_launch_b = gtk_button_new_with_label("Launch raytracing");
	gtk_widget_set_sensitive(iface->i_launch_b, 0);
	iface->i_exit_b = gtk_button_new_with_label("Exit");
	iface->i_enable_blur_sh = gtk_switch_new();
	iface->i_enable_glsampling = gtk_switch_new();
}

static void	set_widgets_in_grid2(t_iface *iface)
{
	gtk_grid_attach(GTK_GRID(iface->i_container),
		iface->labels->gl_sampling, 1, 7, 1, 1);
	gtk_grid_attach(GTK_GRID(iface->i_container),
		iface->i_gl_sampling, 2, 7, 1, 1);
	gtk_grid_attach(GTK_GRID(iface->i_container),
		iface->i_launch_b, 1, 8, 2, 1);
	gtk_grid_attach(GTK_GRID(iface->i_container),
		iface->i_exit_b, 1, 9, 2, 1);
}

void		set_widgets_in_grid(t_iface *iface)
{
	gtk_grid_attach(GTK_GRID(iface->i_container),
		iface->labels->max_depth, 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(iface->i_container),
		iface->i_depth, 2, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(iface->i_container),
		iface->labels->antialiasing, 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(iface->i_container),
		iface->i_antialiasing, 2, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(iface->i_container),
		iface->labels->blur_shadows, 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(iface->i_container),
		iface->i_enable_blur_sh, 2, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(iface->i_container),
		iface->labels->light_spread, 1, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(iface->i_container),
		iface->i_light_spread, 2, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(iface->i_container),
		iface->labels->light_sep, 1, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(iface->i_container),
		iface->i_light_sep, 2, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(iface->i_container),
		iface->labels->gl_enabled, 1, 6, 1, 1);
	gtk_grid_attach(GTK_GRID(iface->i_container),
		iface->i_enable_glsampling, 2, 6, 1, 1);
	set_widgets_in_grid2(iface);
}
