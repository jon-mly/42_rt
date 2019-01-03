/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:04:14 by aabelque          #+#    #+#             */
/*   Updated: 2019/01/03 12:55:52 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			create_srv(t_env *e)
{
	int			opt;

	opt = 1;
	ft_putendl("Creating socket...");
	e->srv.socket = socket(AF_INET, SOCK_STREAM, 0);
	if (e->srv.socket == SOCKET_ERROR)
		ft_error("Server socket creation error");
	e->srv.sin_sz = sizeof(e->srv.sin);
	if (setsockopt(e->srv.socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
				sizeof(opt)) < 0)
		ft_error("setsockopt error");
	e->srv.err = bind(e->srv.socket, (t_sockaddr *)&e->srv.sin, e->srv.sin_sz);
	if (e->srv.err == SOCKET_ERROR)
		ft_error("Server bind error");
	e->srv.err = listen(e->srv.socket, 10);
	if (e->srv.err == SOCKET_ERROR)
		ft_error("listening error");
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
		ft_error("Error function accept()");
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
