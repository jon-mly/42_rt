/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 21:32:18 by guillaume         #+#    #+#             */
/*   Updated: 2019/02/15 14:36:15 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_interface.h"

void	update_depth(GtkWidget *depth_scale, gpointer data)
{
	t_settings	*settings;

	settings = (t_settings*)data;
	settings->depth = gtk_range_get_value(GTK_RANGE(depth_scale));
}

void	update_antialiasing(GtkWidget *antia_scale, gpointer data)
{
	t_settings	*settings;

	settings = (t_settings*)data;
	settings->antialiasing = gtk_range_get_value(GTK_RANGE(antia_scale));
}

void	update_lightspread(GtkWidget *ls_scale, gpointer data)
{
	t_settings	*settings;

	settings = (t_settings*)data;
	settings->light_spread = gtk_range_get_value(GTK_RANGE(ls_scale));
}

void	update_lightsep(GtkWidget *lsep_scale, gpointer data)
{
	t_settings	*settings;

	settings = (t_settings*)data;
	settings->light_sep = gtk_range_get_value(GTK_RANGE(lsep_scale));
}

void	update_glsampling(GtkWidget *gl_scale, gpointer data)
{
	t_settings	*settings;

	settings = (t_settings*)data;
	settings->gl_sampling = gtk_range_get_value(GTK_RANGE(gl_scale));
}
