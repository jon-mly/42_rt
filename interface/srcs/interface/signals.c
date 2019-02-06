/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 21:20:29 by guillaume         #+#    #+#             */
/*   Updated: 2019/02/06 17:34:18 by guillaume        ###   ########.fr       */
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

	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),
											"./rt_scenes/");
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

	printf("RT SETTINGS ARE**********************************\n");
	printf("max depth %d\nantialiasing %d\nblur shadows enable: %d\nlight spread %d\nlight sep %d\nGl_enabled: %d\ngl_sampling %d\nport: %d\nwidth %d | height %d\nscene_file: %s\n", settings->depth,
														settings->antialiasing,
														settings->is_blur_shadows,
														settings->light_spread,
														settings->light_sep,
														settings->is_gl_enabled,
														settings->gl_sampling,
														settings->port,
														settings->render_w,
														settings->render_h,
														settings->scene_file);
	printf("**********************************\n");
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

	bEtat =
		gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gl_sampling_button));
	gtk_widget_set_sensitive(GTK_WIDGET(iface[14]), bEtat);
}

void	update_blursh(GtkWidget *blursh, gpointer data)
{
	t_settings *settings = (t_settings*)data;

	settings->is_blur_shadows =
		gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(blursh));
	show_settings(NULL, settings);
}

void	update_gl_enable(GtkWidget *glenable, gpointer data)
{
	t_settings *settings = (t_settings*)data;

	settings->is_gl_enabled =
		gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(glenable));
	show_settings(NULL, settings);
}

static void	err_dial(t_settings *settings,int err_code, const gchar *msg)
{
		GtkWidget *dialog;
		GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
		settings->err = err_code;
		dialog = gtk_message_dialog_new (NULL,
                                 flags,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "%s",
								 msg);
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
}

static int	port_is_correct(unsigned int	port)
{
	return (port > 1024 && port < 65555);
}

void	launch_rt(GtkButton *button, gpointer user_data)
{
	t_settings	*settings = (t_settings*)user_data;

	if (!settings->scene_file)
		err_dial(settings, SCENE_FILE_ERROR, SCENE_FILE_ERROR_MSG);
	else if (!port_is_correct(settings->port))
		err_dial(settings, PORT_ERROR, PORT_ERROR_MSG);
	else
		settings->err = 1;
	if (settings->err < 0)
		return ;
	if(execlp("./rt", "rt", settings->scene_file, "-p", "4242", (char *)NULL) == -1)
		err_dial(settings, EXECLP_ERROR, EXECLP_ERROR_MSG);
}

void	update_port(GtkEntry *entry, gpointer user_data)
{
	t_settings	*settings = (t_settings*)user_data;

	settings->port = (unsigned int)ft_atoi(gtk_entry_get_text(GTK_ENTRY(entry)));
	show_settings(NULL, settings);
}

void	update_render_size(GtkButton *w, gpointer user_data)
{
	t_settings *settings = (t_settings*)user_data;
	const gchar *w_label = gtk_button_get_label(GTK_BUTTON(w));

	if (!ft_strcmp("900 x 600", w_label))
	{
		settings->render_w = 900;
		settings->render_h = 600;
	}
	else if (!ft_strcmp("1200 x 900", w_label))
	{
		settings->render_w = 1200;
		settings->render_h = 900;
	}
	else if (!ft_strcmp("1500 x 1200", w_label))
	{
		settings->render_w = 1500;
		settings->render_h = 1200;
	}
	else
	{
		err_dial(settings, -4, "erreur render size update");
	}
	show_settings(NULL, settings);
}
