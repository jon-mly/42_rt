/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:04:14 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/21 11:04:45 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			create_srv(t_env *e)
{
	ft_putendl("Creating socket...");
	e->srv.socket = socket(AF_INET, SOCK_STREAM, 0);
	if (e->srv.socket == SOCKET_ERROR)
	{
		ft_putendl("Server socket creation error");
		exit(EXIT_FAILURE);
	}
	e->srv.sin_sz = sizeof(e->srv.sin);
	e->srv.err = bind(e->srv.socket, (t_sockaddr *)&e->srv.sin, e->srv.sin_sz);
	if (e->srv.err == SOCKET_ERROR)
	{
		ft_putendl("Server bind error");
		exit(EXIT_FAILURE);
	}
	e->srv.err = listen(e->srv.socket, 10);
	if (e->srv.err == SOCKET_ERROR)
	{
		ft_putendl("listening error");
		exit(EXIT_FAILURE);
	}
}

void			server_connect(t_env *e)
{
	if (e->srv.nbclient == 10)
	{
		pthread_exit(NULL);
		e->srv.nbclient = 0;
	}
	e->srv.socket_cl = accept(e->srv.socket, (t_sockaddr *)&e->srv.sin,
			&e->srv.sin_sz);
	e->srv.sockets[e->srv.nbclient] = e->srv.socket_cl;
	if (e->srv.socket_cl == SOCKET_ERROR)
	{
		ft_putendl("Error function accept()");
		exit(EXIT_FAILURE);
	}
	else
	{
		e->srv.id++;
		e->srv.nbclient++;
	}
	ft_putendl("Connected to client");
}

void			*await_new_client(void *arg)
{
	t_env		*env;

	env = (t_env *)arg;
	while (1)
		server_connect(env);
	pthread_exit(NULL);
}
