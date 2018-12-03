/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:36 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/11/30 16:45:53 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	ft_putendl("Usage : ./rt [scene file descriptor] -p [1024 > PORT < 65535]");
	exit(0);
}

void		exit_usage2(void)
{
	ft_putendl("Usage : ./client [IP address] -p [1024 > PORT < 65535]");
	exit(0);
}

void		exit_invalid_file(void)
{
	ft_putendl("The file contains invalid characters.");
	exit(0);
}
