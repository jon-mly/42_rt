/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:18:18 by aabelque          #+#    #+#             */
/*   Updated: 2018/11/23 15:32:50 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_env_client(t_env *e, char *str)
{
	e->srv.writefdc = NULL;
	e->srv.hostinfo = NULL;
	e->srv.socket_cl = 0;
	ft_memset(&e->srv.sin_cl, 0, sizeof(e->srv.sin_cl));
	e->srv.hostinfo = gethostbyname(str);
	e->srv.sin_cl.sin_addr = *(struct in_addr *)e->srv.hostinfo->h_addr;
	e->srv.sin_cl.sin_family = AF_INET;
	e->srv.sin_cl.sin_port = e->srv.sin.sin_port;
	ft_bzero(e->srv.readfdc, sizeof(fd_set));
}

void		create_client(t_env *e)
{
	ft_putendl("Creating socket client...");
	e->srv.socket_cl = socket(AF_INET, SOCK_STREAM, 0);
	if (e->srv.socket_cl == SOCKET_ERROR)
	{
		ft_putendl("Client socket creation error");
		exit(EXIT_FAILURE);
	}
	ft_putendl("Socket is open TCP/IP mode");
	e->srv.err = connect(e->srv.socker_cl, (t_sockaddr *)&e->srv.sin,
			sizeof(e->srv.sin));
	if (e->srv.err == SOCKET_ERROR)
	{
		ft_putendl("Error function connect()");
		exit(EXIT_FAILURE);
	}
	FD_ZERO(&e->srv.readfdc);
	FD_SET(e->srv.socket_cl, &e->srv.readfdc);
	if (select(FD_SETSIZE, &e->srv.readfdc, NULL, NULL, NULL) < 0)
	{
		ft_putendl("Error function select()");
		exit(EXIT_FAILURE);
	}
	if (FD_ISSET(e->srv.socket_cl, &e->srv.readfdc))
	{
		e->srv.err = recv_client(e);
		if (e->srv.err == SOCKET_ERROR)
		{
			ft_putendl("Error function send_recv_client()");
			exit(EXIT_FAILURE);
		}
	}
}

int			recv_client(t_env *e)
{
	int		err;
	int		obj_sz;
	int		light_sz;

	err = 0;
	err = recv(e->srv.socket_cl, &e->srv.nbclient, sizeof(int), 0);
	if (err == SOCKET_ERROR)
		return (err);
	err = recv(e->srv.socket_cl, &obj_sz, sizeof(int), 0);
	if (err == SOCKET_ERROR)
		return (err);
	err = recv(e->srv.socket_cl, &light_sz, sizeof(int), 0);
	if (err == SOCKET_ERROR)
		return (err);
	err = recv(e->srv.socket_cl, e->scene.objects, sizeof(t_object) * obj_sz, 0);
	if (err == SOCKET_ERROR)
		return (err);
	err = recv(e->srv.socket_cl, e->scene.lights, sizeof(t_light) * light_sz, 0);
	if (err == SOCKET_ERROR)
		return (err);
	err = recv(e->srv.socket_cl, &e->scene, sizeof(t_scene), 0);
	if (err == SOCKET_ERROR)
		return (err);
	err = recv(e->srv.socket_cl, &e->camera, sizeof(t_camera), 0);
	if (err == SOCKET_ERROR)
		return (err);
	return (err);
}
