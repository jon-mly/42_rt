/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:18:18 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/17 17:31:48 by aabelque         ###   ########.fr       */
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

/*void		loop_data(t_env *e)
{
	while (1)
	{
		recv_client(e);
		opencl_draw(&e->opcl, env);
	}
}*/

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

static	int		recv_nb_light_obj(t_env *e)
{
	e->err = recv(e->srv.socket, &e->srv.id, sizeof(int), 0);
	if (e->err == SOCKET_ERROR)
		return (e->err);
	e->err = recv(e->srv.socket, &e->obj_ct, sizeof(int), 0);
	if (e->err == SOCKET_ERROR)
		return (e->err);
	e->err = recv(e->srv.socket, &e->light_ct, sizeof(int), 0);
	if (e->err == SOCKET_ERROR)
		return (e->err);
	if (!(e->scene.objects = (t_object *)malloc(sizeof(t_object) * e->obj_ct)))
		exit(EXIT_FAILURE);
	if (!(e->scene.lights = (t_light *)malloc(sizeof(t_light) * e->light_ct)))
		exit(EXIT_FAILURE);
	return(e->err);

}

static	int		recv_cam_scene(t_env *e)
{
	e->err = recv(e->srv.socket, &e->camera, sizeof(t_camera), 0);
	if (e->err == SOCKET_ERROR)
		return (e->err);
	return (e->err);
}

int				recv_obj_light(t_env *e)
{
	int 	i;

	i = -1;
	if ((e->err = recv_nb_light_obj(e)) == SOCKET_ERROR)
		return (e->err);
	if ((e->err = recv_cam_scene(e)) == SOCKET_ERROR)
		return (e->err);
	e->scene.lights_count = e->light_ct;
	e->scene.objects_count = e->obj_ct;
	while (++i < e->obj_ct)
	{
		e->err = recv(e->srv.socket, (void *)e->data_o, sizeof(t_object), 0);
		if (e->err == SOCKET_ERROR)
			return (e->err);
		deserialize_obj(e->data_o, &e->scene.objects[i]);
	}
	i = -1;
	while (++i < e->light_ct)
	{
		ft_bzero(e->data_l, sizeof(t_light));
		e->err = recv(e->srv.socket, (void *)e->data_l, sizeof(t_light), 0);
		if (e->err == SOCKET_ERROR)
			return (e->err);
		deserialize_light(e->data_l, &e->scene.lights[i]);
	}
	return (e->err);
}
