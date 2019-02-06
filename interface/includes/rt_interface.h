/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_interface.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 16:25:13 by gmajstru          #+#    #+#             */
/*   Updated: 2019/02/06 17:57:42 by aabelque         ###   ########.fr       */
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
	unsigned int	depth;
	unsigned int	antialiasing;
	gboolean		is_blur_shadows;
	unsigned int	light_spread;
	unsigned int	light_sep;
	gboolean		is_gl_enabled;
	unsigned int	gl_sampling;
	unsigned int	port;
	unsigned int	render_w;
	unsigned int	render_h;
	char			*scene_file;
}						t_settings;

t_settings				*init_settings(void);
void					launch_rt(GtkButton *button, gpointer user_data);
void					select_file(GtkWidget *w, gpointer user_data);
void					show_settings(GtkWidget *w, gpointer user_data);
void					blur_shadows_e_d(GtkWidget *blur_button, gpointer data);
void					gl_sampling_e_d(GtkWidget *gl_sampling_button, gpointer data);
void					update_blursh(GtkWidget *blursh, gpointer data);
void					update_gl_enable(GtkWidget *glenable, gpointer data);
void					update_depth(GtkWidget *depth_scale, gpointer data);
void					update_antialiasing(GtkWidget *antia_scale, gpointer data);
void					update_lightspread(GtkWidget *ls_scale, gpointer data);
void					update_lightsep(GtkWidget *lsep_scale, gpointer data);
void					update_glsampling(GtkWidget *gl_scale, gpointer data);
void					update_port(GtkEntry *entry, gpointer user_data);
void					update_render_size(GtkButton *w, gpointer user_data);
#endif
