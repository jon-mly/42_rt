/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:24:22 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/10 18:54:07 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			*waitcl(void *arg)
{
	t_env		e;
	pthread_t	thr;
	
	e = *(t_env *)arg;
	while (1)
	{
		server_connect(&e);
		if (pthread_create(&thr, NULL, loop_data, &e))
		{
			ft_putendl("Error function pthread_create()");
			exit(EXIT_FAILURE);
		}
	}
	return (NULL);
}

void			*loop_data(void *arg)
{
	t_env		*e;
	int			err;

	e = (t_env *)arg;
	//while (1)
	//{
	if ((err = send_data(e)) == SOCKET_ERROR)
	{
		perror("send()");
		exit(EXIT_FAILURE);
	}
	//}
	return (NULL);
}
