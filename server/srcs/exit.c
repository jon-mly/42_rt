/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:36 by jmlynarc          #+#    #+#             */
/*   Updated: 2019/02/16 18:19:40 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		exit_error(t_env *env)
{
	ft_putendl("An error has occured");
	deinit_env(env);
	exit(0);
}

void		exit_normally(t_env *env)
{
	deinit_env(env);
	exit(0);
}

void		exit_usage(void)
{
	char	*str1;

	str1 = ft_strdup("Usage : ");
	str1 = ft_strjoin(str1,
	" ./rt [scene file descriptor] -p port max_depth aliasing blur_shadows ");
	str1 = ft_strjoin(str1,
	" light_spread light_sep gi_enabled gi_sampling width height\n");
	str1 = ft_strjoin(str1,
	"\tmax_depth -> [1:10]\n\taliasing [0:4]\n\tif blur_shadows is enabled:");
	str1 = ft_strjoin(str1,
	"\n\t\tlight_spread -> [1:3]\n\t\tlight_sep -> [1:3]\n\t");
	str1 = ft_strjoin(str1,
	"if global illumination max iteration is enabled (gi_enabled):\n\t\t");
	str1 = ft_strjoin(str1, "gi_sampling -> [20 : 50]\n\t");
	str1 = ft_strjoin(str1, "width = 900|1200|1500 / height = 600|900|1200");
	str1 = ft_strjoin(str1,
		"\n\t\tyou must set height according to the width i.e: 900 -> 600");
	ft_putendl(str1);
	ft_strdel(&str1);
	exit(0);
}

void		exit_invalid_file(void)
{
	ft_putendl("The file contains invalid characters.");
	exit(0);
}
