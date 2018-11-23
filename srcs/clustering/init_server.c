/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:04:14 by aabelque          #+#    #+#             */
/*   Updated: 2018/11/23 16:03:46 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			init_env_server(t_env *e, char *str)
{
	e->srv.port = ft_atoi(str);
	e->srv.nbclient = 1;
	e->srv.sz = 0;
	e->srv.sockmax = 0;
	e->srv.nb_cl = NULL;
	e->srv.writefds = NULL;
	e->srv.socket = 0;
	e->srv.err = 0;
	e->srv.size_cl = 0;
	e->srv.sin_sz = 0;
	ft_memset(&e->srv.sin, 0, sizeof(e->srv.sin));
	e->srv.sin.sin_addr.s_addr = htonl(INADDR_ANY);
	e->srv.sin.sin_family = AF_INET;
	e->srv.sin.sin_port = htons(e->srv.port);
	ft_bzero(e->srv.readfds, sizeof(fd_set));
}

void			create_srv(t_env *e)
{
	ft_putendl("Creating socket...");
	e->srv.socket = socket(AF_INET, SOCK_STREAM, 0);
	if (e->srv.socket == SOCKET_ERROR)
	{
		ft_putendl("Server socket creation error");
		exit(EXIT_FAILURE);
	}
	e->srv->sin_sz = sizeof(e->srv.sin);
	ft_putendl("Binding socket with addr...");
	e->srv.err = bind(e->srv.socket, (t_sockaddr *)&e->srv.sin, e->srv.sin_sz);
	if (e->srv.err == SOCKET_ERROR)
	{
		ft_putendl("Server bind error");
		exit(EXIT_FAILURE);
	}
	ft_putstr("Listening port ");
	ft_putnbr(e->srv.port);
	ft_putstr("...\n");
	e->srv.err = listen(e->srv.socket, 5);
	if (e->srv.err == SOCKET_ERROR)
	{
		ft_putendl("listening error");
		exit(EXIT_FAILURE);
	}
}

static	void	server_connect2(t_env *e)
{
	int		i;

	i = 0;
	e->srv.fd[0] = e->srv.socket;
	e->srv.sz++;
	e->srv.nbclient++;
	FD_ZERO(&e->srv.readfds);
	FD_ZERO(e->srv.writefds);
	while (i++ < e->srv.sz)
	{
		if (e->srv.fd[i] != 0)
		{
			FD_SET(e->srv.socket, &e->srv.readfds);
			FD_SET(e->srv.socket, e->srv.writefds);
		}
		if (e->srv.sockmax < e->srv.fd[i])
			e->srv.sockmax = e->srv.fd[i];
	}
}

void			server_connect(t_env *e)
{
	server_connect2(e);
	if ((e->srv.err = select(e->srv.sockmax + 1, &e->srv.readfds,
					e->srv.writefds, NULL, NULL)) < 0)
	{
		ft_putendl("Error function select()");
		exit(EXIT_FAILURE);
	}
	if (FD_ISSET(e->srv.socket, &e->srv.readfds))
	{
		ft_putendl("Connecting client...");
		e->srv.socket_cl = accept(e->srv.socket, (t_sockaddr *)&e->srv.sin_cl,
				&e->srv.size_cl);
		if (e->srv.socket_cl == SOCKET_ERROR)
		{
			ft_putendl("Error function accept()");
			exit(EXIT_FAILURE);
		}
		sleep(2);
		send_server(e);
	}
}

int				send_server(t_env *e)
{
	int		err;

	err = 0;
	err = send(e->srv.socket, &e->srv.nbclient, sizeof(int), 0);
	if (err == SOCKET_ERROR)
		return (err);
	err = send(e->srv.socket, &e->scene.objects_count, sizeof(int), 0);
	if (err == SOCKET_ERROR)
		return (err);
	err = send(e->srv.socket, &e->scene.lights_count, sizeof(int), 0);
	if (err == SOCKET_ERROR)
		return (err);
	err = send(e->srv.socket, e->scene.objects,
			sizeof(t_object) * e->scene.objects_count, 0);
	if (err == SOCKET_ERROR)
		return (err);
	err = send(e->srv.socket, e->scene.lights,
			sizeof(t_light) * e->scene.lights_count, 0);
	if (err == SOCKET_ERROR)
		return (err);
	err = send(e->srv.socket, &e->scene, sizeof(t_scene), 0);
	if (err == SOCKET_ERROR)
		return (err);
	err = send(e->srv.socket, &e->camera, sizeof(t_camera), 0);
	if (err == SOCKET_ERROR)
		return (err);
	return (err);
}
