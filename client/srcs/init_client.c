/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:18:18 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/21 18:34:15 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			init_env_client(t_env *e, char *str)
{
	e->srv.hostinfo = NULL;
	e->srv.socket_cl = 0;
	e->srv.socket = 0;
	e->obj_ct = 0;
	e->light_ct = 0;
	e->srv.err = 0;
	e->err = 0;
	ft_memset(&e->srv.sin_cl, 0, sizeof(e->srv.sin_cl));
	e->srv.hostinfo = gethostbyname(str);
	e->srv.sin_cl.sin_addr = *(struct in_addr *)e->srv.hostinfo->h_addr;
	e->srv.sin_cl.sin_family = AF_INET;
	e->srv.sin_cl.sin_port = htons(e->srv.port);
}

void			create_client(t_env *e)
{
	ft_putendl("Connecting to server...");
	e->srv.socket = socket(AF_INET, SOCK_STREAM, 0);
	if (e->srv.socket == SOCKET_ERROR)
	{
		ft_putendl("Client socket creation error");
		exit(EXIT_FAILURE);
	}
	e->srv.err = connect(e->srv.socket, (t_sockaddr *)&e->srv.sin_cl,
			sizeof(e->srv.sin_cl));
	if (e->srv.err == SOCKET_ERROR)
	{
		ft_putendl("Error function connect()");
		exit(EXIT_FAILURE);
	}
}
