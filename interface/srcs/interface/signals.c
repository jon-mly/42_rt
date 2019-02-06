/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 21:20:29 by guillaume         #+#    #+#             */
/*   Updated: 2019/02/05 16:12:37 by guillaume        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_interface.h"

void	select_file(GtkWidget *w, gpointer user_data)
{
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;
	t_settings *settings = (t_settings*)user_data;

	dialog = gtk_file_chooser_dialog_new ("Open File",
										NULL,
										action,
										"_Cancel",
										GTK_RESPONSE_CANCEL,
										"_Open",
										GTK_RESPONSE_ACCEPT,
										NULL);

	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), "./rt_scenes/");
	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		char *filename;
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		filename = gtk_file_chooser_get_filename (chooser);
		settings->scene_file = ft_strdup(filename);
		g_free (filename);
	}
	gtk_widget_destroy (dialog);
}

//DEBUG SIGNAL
void	show_settings(GtkWidget *w, gpointer user_data)
{
	t_settings *settings = (t_settings*)user_data;

	printf("max depth %d\nantialiasing %d\nblur shadows enable: %d\nlight spread %d\nlight sep %d\nGl_enabled: %d\ngl_sampling %d\nport: %d\nscene_file: %s\n", settings->depth,
														settings->antialiasing,
														settings->is_blur_shadows,
														settings->light_spread,
														settings->light_sep,
														settings->is_gl_enabled,
														settings->gl_sampling,
														settings->port,
														settings->scene_file);
}

void	blur_shadows_e_d(GtkWidget *blur_button, gpointer data)
{
	gboolean bEtat;
	GtkWidget	**iface = (GtkWidget**)data;

	bEtat = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(blur_button));
	gtk_widget_set_sensitive(GTK_WIDGET(iface[11]), bEtat);
	gtk_widget_set_sensitive(GTK_WIDGET(iface[12]), bEtat);
}

void	gl_sampling_e_d(GtkWidget *gl_sampling_button, gpointer data)
{
	gboolean bEtat;
	GtkWidget	**iface = (GtkWidget**)data;

	bEtat = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gl_sampling_button));
	gtk_widget_set_sensitive(GTK_WIDGET(iface[14]), bEtat);
}

void	update_blursh(GtkWidget *blursh, gpointer data)
{
	t_settings *settings = (t_settings*)data;

	settings->is_blur_shadows = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(blursh));
}

void	update_gl_enable(GtkWidget *glenable, gpointer data)
{
	t_settings *settings = (t_settings*)data;

	settings->is_gl_enabled = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(glenable));
}

void	launch_rt(GtkButton *button, gpointer user_data)
{
	t_settings	*settings = (t_settings*)user_data;

	if (!settings->scene_file)
	{
		GtkWidget *dialog;
		GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
		dialog = gtk_message_dialog_new (NULL,
                                 flags,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "AUCUN FICHIER DE SCENE SELECTIONNE !");
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
		return ;
	}
	if (execlp("./rt", "rt",
		settings->scene_file, "-p",
				"4242", (char *)NULL) == -1)
	{
		ft_putendl("Error function execlp()");
		exit(EXIT_FAILURE);
	}
}

void	update_port(GtkEntry *entry, gpointer user_data)
{
	t_settings	*settings = (t_settings*)user_data;

	settings->port = (unsigned int)ft_atoi(gtk_entry_get_text(GTK_ENTRY(entry)));
}
