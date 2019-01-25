/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_interface.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmajstru <gmajstru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 16:25:13 by gmajstru          #+#    #+#             */
/*   Updated: 2019/01/25 20:21:30 by gmajstru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_INTERFACE_H
# define RT_INTERFACE_H

# include <gtk/gtk.h>
# include <stdio.h>
# include <stdlib.h>
# include "../../libft/libft.h"

typedef struct			s_user_data
{
	int		ac;
	char	**av;
}						t_data;

typedef struct			s_labels
{
	GtkWidget	*max_depth;
	GtkWidget	*antialiasing;
	GtkWidget	*blur_shadows;
	GtkWidget	*light_spread;
	GtkWidget	*light_sep;
	GtkWidget	*gl_enabled;
	GtkWidget	*gl_sampling;
	GtkWidget	*scene_file_lb;
}						t_labels;

typedef struct			s_g_interface
{
	t_labels	*labels;
	GtkWidget	*window;
	GtkWidget	*i_container;
	GtkWidget	*i_launch_b;
	GtkWidget	*i_exit_b;
	GtkWidget	*i_depth;
	GtkWidget	*i_antialiasing;
	GtkWidget	*i_enable_blur_sh;
	GtkWidget	*i_light_spread;
	GtkWidget	*i_light_sep;
	GtkWidget	*i_enable_glsampling;
	GtkWidget	*i_gl_sampling;
}						t_iface;

typedef struct			s_settings
{
	unsigned int	depth;
	unsigned int	antialiasing;
	unsigned int	is_blur_shadows;
	unsigned int	light_spread;
	unsigned int	light_sep;
	unsigned int	is_gl_enabled;
	unsigned int	gl_sampling;
	char			*scene_file;
}						t_settings;

typedef struct			s_gtk_env
{
	t_data			datas;
	t_settings		*rt_settings;
	t_iface			*iface;
}						t_g_env;

t_settings				*init_settings(void);
t_iface					*init_interface();
t_g_env					*init_gtk_env(int ac, char **av);
void					gtk_deinit_exit(GtkButton *exit_b, gpointer g_datas);
void					launch_rt(GtkButton *button, gpointer user_data);
GtkWidget				*new_window(const gchar *title, gint width,
							gint height);
GtkWidget				*new_grid_layout(GtkWidget *container_to_add,
							gboolean homogeneous_col,
							gboolean homogeneous_row);
t_labels				*init_labels(void);
void					iface_widgets_init(t_iface *iface);
void					set_widgets_in_grid(t_iface *iface);

#endif
