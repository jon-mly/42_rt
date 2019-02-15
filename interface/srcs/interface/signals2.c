/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 23:40:43 by guillaume         #+#    #+#             */
/*   Updated: 2019/02/15 14:33:51 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_interface.h"

void	err_dial(t_settings *settings, int err_code, const gchar *msg)
{
	GtkWidget			*dialog;
	GtkDialogFlags		flags;

	settings->err = err_code;
	flags = GTK_DIALOG_DESTROY_WITH_PARENT;
	dialog = gtk_message_dialog_new(NULL, flags, GTK_MESSAGE_ERROR,
			GTK_BUTTONS_CLOSE, "%s", msg);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

int		port_is_correct(unsigned int port)
{
	return (port > 1024 && port < 65555);
}

void	launch_rt(GtkButton *button, gpointer user_data)
{
	t_settings			*settings;

	settings = (t_settings*)user_data;
	if (!settings->scene_file)
		err_dial(settings, SCENE_FILE_ERROR, SCENE_FILE_ERROR_MSG);
	else if (!port_is_correct(settings->port))
		err_dial(settings, PORT_ERROR, PORT_ERROR_MSG);
	else
		settings->err = 1;
	if (settings->err < 0)
		return ;
	if (execlp("./rt", "rt", settings->scene_file, "-p",
		ft_itoa(settings->port),
		ft_itoa(settings->depth),
		ft_itoa(settings->antialiasing),
		ft_itoa(settings->is_blur_shadows),
		ft_itoa(settings->light_spread),
		ft_itoa(settings->light_sep),
		ft_itoa(settings->is_gl_enabled),
		ft_itoa(settings->gl_sampling),
		ft_itoa(settings->render_w),
		ft_itoa(settings->render_h),
		(char *)NULL) == -1)
		err_dial(settings, EXECLP_ERROR, EXECLP_ERROR_MSG);
}

void	update_port(GtkEntry *entry, gpointer user_data)
{
	t_settings			*s;

	s = (t_settings*)user_data;
	s->port = (unsigned int)ft_atoi(gtk_entry_get_text(GTK_ENTRY(entry)));
}

void	update_render_size(GtkButton *w, gpointer user_data)
{
	t_settings			*settings;
	const gchar			*w_label;

	settings = (t_settings*)user_data;
	w_label = gtk_button_get_label(GTK_BUTTON(w));
	if (!ft_strcmp("900 x 600", w_label))
	{
		settings->render_w = 900;
		settings->render_h = 600;
	}
	else if (!ft_strcmp("1350 x 900", w_label))
	{
		settings->render_w = 1350;
		settings->render_h = 900;
	}
	else if (!ft_strcmp("2025 x 1350", w_label))
	{
		settings->render_w = 2025;
		settings->render_h = 1350;
	}
	else
		err_dial(settings, -4, "erreur render size update");
}
