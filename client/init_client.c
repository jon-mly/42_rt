/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:18:18 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/12 18:39:09 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void		init_env_client(t_env *e, char *str)
{
	e->srv.hostinfo = NULL;
	e->srv.socket_cl = 0;
	e->srv.socket = 0;
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

int			recv_client(t_env *e)
{
	int		err;
	int		obj_ct;
	int		light_ct;

	err = 0;
	err = recv(e->srv.socket, &e->srv.id, sizeof(int), 0);
	if (err == SOCKET_ERROR)
	{
		puts("1");
		perror("recv()");
		return (err);
	}
	err = recv(e->srv.socket, &obj_ct, sizeof(int), 0);
	if (err == SOCKET_ERROR)
	{
		puts("2");
		perror("recv()");
		return (err);
	}
	err = recv(e->srv.socket, &light_ct, sizeof(int), 0);
	if (err == SOCKET_ERROR)
	{
		puts("3");
		perror("recv()");
		return (err);
	}
	char	data[SIZE_OBJ * obj_ct];
	if (!(e->scene.objects = (t_object *)malloc(sizeof(t_object) * obj_ct)))
		exit(EXIT_FAILURE);
	err = recv(e->srv.socket, (void *)data, sizeof(t_object) * obj_ct, 0);
	if (err == SOCKET_ERROR)
	{
		puts("4");
		perror("recv()");
		return (err);
	}
	write(1, "X\n", 2);
	deserialize_obj(data, e->scene.objects);
	write(1, "X\n", 2);
	if (!(e->scene.lights = (t_light *)malloc(sizeof(t_light) * light_ct)))
		exit(EXIT_FAILURE);
	err = recv(e->srv.socket, e->scene.lights, sizeof(t_light) * light_ct, 0);
	if (err == SOCKET_ERROR)
	{
		puts("5");
		perror("recv()");
		return (err);
	}
	err = recv(e->srv.socket, &e->scene, sizeof(t_scene), 0);
	if (err == SOCKET_ERROR)
	{
		puts("6");
		perror("recv()");
		return (err);
	}
	write(1, "ici\n", 4);
	printf("client obj angle %f\n", e->scene.objects->angle);
//	printf("client obj count %d\n", e->scene.objects_count);
	write(1, "R\n", 2);
//	printf("light %p\n", e->scene.lights);
//	printf("client angle %f\n", e->scene.lights->angle);
	write(1, "R\n", 2);
	printf("client angle test");
	write(1, "R\n", 2);
	err = recv(e->srv.socket, &e->camera, sizeof(t_camera), 0);
	if (err == SOCKET_ERROR)
	{
		puts("7");
		perror("recv()");
		return (err);
	}
	//e->scene.objects_count = obj_ct;
	//e->scene.lights_count = light_ct;
	printf("client obj count %d\n", e->scene.objects_count);
	printf("client light count %d\n", e->scene.lights_count);
	printf("client cam width %f\n", e->camera.width);
	return (err);
}
