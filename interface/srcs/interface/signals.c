/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 21:20:29 by guillaume         #+#    #+#             */
/*   Updated: 2019/02/15 14:24:38 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_interface.h"

void		select_file(GtkWidget *w, gpointer user_data)
{
	GtkWidget				*dialog;
	GtkFileChooserAction	action;
	gint					res;
	t_settings				*settings;
	char					*filename;
	GtkFileChooser			*chooser;

	settings = (t_settings*)user_data;
	action = GTK_FILE_CHOOSER_ACTION_OPEN;
	dialog = gtk_file_chooser_dialog_new("Open File",
			NULL, action, "_Cancel", GTK_RESPONSE_CANCEL, "_Open",
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

void		blur_shadows_e_d(GtkWidget *blur_button, gpointer data)
{
	gboolean				betat;
	GtkWidget				**iface;

	iface = (GtkWidget**)data;
	betat = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(blur_button));
	gtk_widget_set_sensitive(GTK_WIDGET(iface[11]), betat);
	gtk_widget_set_sensitive(GTK_WIDGET(iface[12]), betat);
}

void		gl_sampling_e_d(GtkWidget *gl_sampling_button, gpointer data)
{
	gboolean				betat;
	GtkWidget				**iface;

	iface = (GtkWidget**)data;
	betat =
		gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gl_sampling_button));
	gtk_widget_set_sensitive(GTK_WIDGET(iface[14]), betat);
}

void		update_blursh(GtkWidget *blursh, gpointer data)
{
	t_settings				*settings;

	settings = (t_settings*)data;
	settings->is_blur_shadows =
		gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(blursh));
}

void		update_gl_enable(GtkWidget *glenable, gpointer data)
{
	t_settings				*settings;

	settings = (t_settings*)data;
	settings->is_gl_enabled =
		gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(glenable));
}
