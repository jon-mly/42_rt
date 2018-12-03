/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:18:18 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/03 19:25:03 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_env_client(t_env *e, char *str)
{
	e->srv.hostinfo = NULL;
	e->srv.socket_cl = 0;
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

void		create_client(t_env *e)
{
	ft_putendl("Connecting to server...");
	e->srv.socket_cl = socket(AF_INET, SOCK_STREAM, 0);
	if (e->srv.socket_cl == SOCKET_ERROR)
	{
		ft_putendl("Client socket creation error");
		exit(EXIT_FAILURE);
	}
	e->srv.err = connect(e->srv.socket_cl, (t_sockaddr *)&e->srv.sin_cl,
			sizeof(e->srv.sin_cl));
	if (e->srv.err == SOCKET_ERROR)
	{
		printf("%d\n", e->srv.err);
		perror("connect()");
		ft_putendl("Error function connect()");
		exit(EXIT_FAILURE);
	}
}

int			recv_client(t_env *e)
{
	int		err;
	int		obj_sz;
	int		light_sz;

	err = 0;
	err = recv(e->srv.socket_cl, &e->srv.id, sizeof(int), 0);
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
	printf("%d\n", obj_sz);
	return (err);
}
