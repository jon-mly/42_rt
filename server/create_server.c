/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:04:14 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/19 16:20:16 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

void			*await_new_client(void *arg)
{
	t_env		*env;

	env = (t_env *)arg;
	while (1)
		server_connect(env);
	pthread_exit(NULL);
}

static	int		send_nb_light_obj(t_env *e)
{
	e->err = send(e->srv.socket_cl, &e->srv.id, sizeof(int), 0);
	if (e->err == SOCKET_ERROR)
	{
		perror("send()");
		return (e->err);
	}
	e->err = send(e->srv.socket_cl, &e->scene.objects_count, sizeof(int), 0);
	if (e->err == SOCKET_ERROR)
	{
		perror("send()");
		return (e->err);
	}
	e->err = send(e->srv.socket_cl, &e->scene.lights_count, sizeof(int), 0);
	if (e->err == SOCKET_ERROR)
	{
		perror("send()");
		return (e->err);
	}
	return (e->err);
}

static t_render_bounds	bounds_at(int socket_index, int sockets_count)
{
	t_render_bounds		bounds;

	bounds.top = (int)floor(WIN_HEIGHT * ((float)socket_index / (float)sockets_count));
	bounds.bottom = (int)floor(WIN_HEIGHT * ((float)(socket_index + 1) / (float)sockets_count)) - 1;
	return (bounds);
}

static int		send_render_bounds(t_env *e)
{
	e->err = send(e->srv.socket_cl, (void*)&e->bounds, sizeof(t_render_bounds), 0);
	return (e->err);	
}

static	int		send_cam_scene(t_env *e)
{
	e->err = send(e->srv.socket_cl, &e->camera, sizeof(t_camera), 0);
	return (e->err);
}

int				send_obj_light(t_env *e)
{
	int		i;

	i = -1;
	if ((e->err = send_nb_light_obj(e)) == SOCKET_ERROR)
	{
		perror("send()");
		return (e->err);
	}
	e->bounds = bounds_at(e->srv.crrnt_sckt_id, e->srv.nbclient);
	if ((e->err = send_render_bounds(e)) == SOCKET_ERROR)
	{
		ft_putendl("Rendering bounds sending did fail");
		perror("send()");
		return (e->err);
	}
	if ((e->err = send_cam_scene(e)) == SOCKET_ERROR)
	{
		perror("send()");
		return (e->err);
	}
	while (++i < e->scene.objects_count)
	{
		serialize_obj(&e->scene.objects[i], e->data_o);
		e->err = send(e->srv.socket_cl, (void *)e->data_o, sizeof(t_object), 0);
		if (e->err == SOCKET_ERROR)
		{
			perror("send()");
			return (e->err);
		}
		nanosleep(&e->tim, &e->tim);
	}
	i = -1;
	while (++i < e->scene.lights_count)
	{
		serialize_light(&e->scene.lights[i], e->data_l);
		e->err = send(e->srv.socket_cl, (void *)e->data_l, sizeof(t_light), 0);
		if (e->err == SOCKET_ERROR)
		{
			perror("send()");
			return (e->err);
		}
	}
	return (e->err);
}
