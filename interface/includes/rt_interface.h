/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_interface.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 16:25:13 by gmajstru          #+#    #+#             */
/*   Updated: 2019/02/14 23:47:03 by guillaume        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_INTERFACE_H
# define RT_INTERFACE_H

# include <gtk/gtk.h>
# include <stdio.h>
# include <stdlib.h>
# include "../../libft/libft.h"

# define PORT_ERROR -1
# define PORT_ERROR_MSG "Port is not within the good range\
 please select a port beetween [ 1024 > PORT < 65555 ]"

# define SCENE_FILE_ERROR -2
# define SCENE_FILE_ERROR_MSG "No scene file selected, please\
 select a scene file to launch rt"

# define EXECLP_ERROR -3
# define EXECLP_ERROR_MSG "Error function execlp()"

typedef struct			s_user_data
{
	int		ac;
	char	**av;
}						t_data;

typedef struct			s_settings
{
	int				err;
	int				is_blur_shadows;
	int				is_gl_enabled;
	unsigned int	depth;
	unsigned int	antialiasing;
	unsigned int	light_spread;
	unsigned int	light_sep;
	unsigned int	gl_sampling;
	unsigned int	port;
	unsigned int	render_w;
	unsigned int	render_h;
	char			*scene_file;
}						t_settings;

typedef struct	s_interface
{
	t_settings	*rt_set;
	GtkWidget	*window;
	GtkWidget	*master_grid;
	GtkWidget	*grid_widget;
	GtkWidget	*graph_frame;
	GtkWidget	*w_size_frame;
	GtkWidget	*w_size_grid;
	GtkWidget	*server_frame;
	GtkWidget	*server_grid;
	GtkWidget	*server_w[2];
	GtkWidget	*iface_w[17];
	GtkWidget	*size_buttons[3];
}				t_inter;

t_settings				*init_settings(void);
void					launch_rt(GtkButton *button, gpointer user_data);
void					select_file(GtkWidget *w, gpointer user_data);
void					show_settings(GtkWidget *w, gpointer user_data);
void					blur_shadows_e_d(GtkWidget *blur_button,
							gpointer data);
void					gl_sampling_e_d(GtkWidget *gl_sampling_button,
							gpointer data);
void					update_blursh(GtkWidget *blursh, gpointer data);
void					update_gl_enable(GtkWidget *glenable, gpointer data);
void					update_depth(GtkWidget *depth_scale, gpointer data);
void					update_antialiasing(GtkWidget *antia_scale,
							gpointer data);
void					update_lightspread(GtkWidget *ls_scale, gpointer data);
void					update_lightsep(GtkWidget *lsep_scale, gpointer data);
void					update_glsampling(GtkWidget *gl_scale, gpointer data);
void					update_port(GtkEntry *entry, gpointer user_data);
void					update_render_size(GtkButton *w, gpointer user_data);
GtkWidget				*create_window(const gchar *title);
GtkWidget				*create_grid(gboolean c_hom, gboolean r_hom,
							guint border_width);
GtkWidget				*create_frame(const gchar *title, guint border_width);
void					attach_widgets_grid(GtkWidget **lbls,
							GtkWidget *grid, guint size);
void					init_iface_w(GtkWidget **iface_w);
void					init_range_values(GtkWidget **iface_w,
							t_settings *rt_set);
void					connect_widgets_signals(GtkWidget **iface_w,
							t_settings *rt_set);
void					init_size_w(GtkWidget **size_buttons,
							GtkWidget *w_size_grid, t_settings *rt_set);
void					init_server_w(GtkWidget **server_w,
							GtkWidget *server_grid, t_settings *rt_set);
t_inter					new_interface();
void					setup_grids(t_inter *inter);
void					err_dial(t_settings *settings,int err_code,
							const gchar *msg);
int						port_is_correct(unsigned int port);
#endif
