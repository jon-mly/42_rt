/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 21:20:29 by guillaume         #+#    #+#             */
/*   Updated: 2019/02/01 22:07:53 by guillaume        ###   ########.fr       */
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

	printf("max depth %d\nantialiasing %d\nblur shadows enable: %d\nlight spread %d\nlight sep %d\nGl_enabled: %d\ngl_sampling %d\nscene_file: %s\n", settings->depth,
														settings->antialiasing,
														settings->is_blur_shadows,
														settings->light_spread,
														settings->light_sep,
														settings->is_gl_enabled,
														settings->gl_sampling,
														settings->scene_file);
}

void	blur_shadows_e_d(GtkWidget *blur_button, gpointer data)
{
	gboolean bEtat;
	GtkWidget	**iface = (GtkWidget**)data;

	bEtat = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(blur_button));
	gtk_widget_set_sensitive(GTK_WIDGET(iface[3]), bEtat);
	gtk_widget_set_sensitive(GTK_WIDGET(iface[4]), bEtat);
}

void	gl_sampling_e_d(GtkWidget *gl_sampling_button, gpointer data)
{
	gboolean bEtat;
	GtkWidget	**iface = (GtkWidget**)data;

	bEtat = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gl_sampling_button));
	gtk_widget_set_sensitive(GTK_WIDGET(iface[6]), bEtat);
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
		GtkWidget *dialog, *label, *content_area;
		GtkDialogFlags flags;

		// Create the widgets
		flags = GTK_DIALOG_DESTROY_WITH_PARENT;
		dialog = gtk_dialog_new_with_buttons ("Message",
											NULL,
											flags,
											"OK",
											GTK_RESPONSE_NONE,
											NULL);
		content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
		label = gtk_label_new ("Veuillez selectionner un fichier de scene avant de lancer le rendu !");
		g_signal_connect_swapped (dialog,
								"response",
								G_CALLBACK (gtk_widget_destroy),
								dialog);
		gtk_container_add (GTK_CONTAINER (content_area), label);
		gtk_widget_show_all (dialog);
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
