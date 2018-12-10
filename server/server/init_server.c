/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:04:14 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/10 18:54:11 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	void	quit(int sig)
{
	(void)sig;
	sleep(1);
	exit(EXIT_SUCCESS);
}

void			init_env_server(t_env *e)
{
	signal(SIGTERM, quit);
	signal(SIGQUIT, quit);
	signal(SIGINT, quit);
	signal(SIGPIPE, quit);
	e->srv.id = -1;
	e->srv.nbclient = 0;
	e->srv.sz = 0;
	e->srv.sockmax = 0;
	e->srv.socket = 0;
	e->srv.err = 0;
	e->srv.size_cl = 0;
	e->srv.sin_sz = 0;
	ft_memset(&e->srv.sin, 0, sizeof(e->srv.sin));
	e->srv.sin.sin_addr.s_addr = htonl(INADDR_ANY);
	e->srv.sin.sin_family = AF_INET;
	e->srv.sin.sin_port = htons(e->srv.port);
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
	e->srv.sin_sz = sizeof(e->srv.sin);
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

void			server_connect(t_env *e)
{
	if (e->srv.nbclient == 4)
		pthread_exit(NULL);
	ft_putendl("Connecting client...");
	e->srv.socket_cl = accept(e->srv.socket, (t_sockaddr *)&e->srv.sin,
			&e->srv.sin_sz);
	printf("sockcl %d\n", e->srv.socket_cl);
	printf("sock %d\n", e->srv.socket);
	if (e->srv.socket_cl == SOCKET_ERROR)
	{
		ft_putendl("Error function accept()");
		perror("accept()");
		exit(EXIT_FAILURE);
	}
	else
	{
		e->srv.id++;
		e->srv.nbclient++;
	}
	ft_putendl("Connected to client");
}

int				send_data(t_env *e)
{
	int		err;

	err = 0;
	err = send(e->srv.socket_cl, &e->srv.id, sizeof(int), 0);
	if (err == SOCKET_ERROR)
		return (err);
	err = send(e->srv.socket_cl, &e->scene.objects_count, sizeof(int), 0);
	if (err == SOCKET_ERROR)
		return (err);
	err = send(e->srv.socket_cl, &e->scene.lights_count, sizeof(int), 0);
	if (err == SOCKET_ERROR)
		return (err);
	err = send(e->srv.socket_cl, e->scene.objects,
			sizeof(t_object) * e->scene.objects_count, 0);
	if (err == SOCKET_ERROR)
		return (err);
	err = send(e->srv.socket_cl, e->scene.lights,
			sizeof(t_light) * e->scene.lights_count, 0);
	if (err == SOCKET_ERROR)
		return (err);
	err = send(e->srv.socket_cl, &e->scene, sizeof(t_scene), 0);
	if (err == SOCKET_ERROR)
		return (err);
	err = send(e->srv.socket_cl, &e->camera, sizeof(t_camera), 0);
	if (err == SOCKET_ERROR)
		return (err);
	return (err);
} 
