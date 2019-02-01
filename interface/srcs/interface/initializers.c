/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 19:25:37 by gmajstru          #+#    #+#             */
/*   Updated: 2019/02/01 21:17:32 by guillaume        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_interface.h"

t_settings	*init_settings(void)
{
	t_settings	*settings;

	settings = NULL;
	if (!(settings = (t_settings*)malloc(sizeof(t_settings))))
	{
		ft_putendl("settings malloc failure !");
		return (settings);
	}
	settings->depth = 0;
	settings->antialiasing = 0;
	settings->is_blur_shadows = FALSE;
	settings->light_spread = 0;
	settings->light_sep = 0;
	settings->is_gl_enabled = FALSE;
	settings->gl_sampling = 0;
	settings->scene_file = NULL;
	return (settings);
}
