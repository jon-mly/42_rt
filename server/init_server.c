/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:04:14 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/13 19:17:50 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*static	void	quit(int sig)
{
	(void)sig;
	sleep(1);
	exit(EXIT_SUCCESS);
}
*/
void			init_env_server(t_env *e)
{
	//signal(SIGTERM, quit);
	//signal(SIGQUIT, quit);
	//signal(SIGINT, quit);
	//signal(SIGPIPE, quit);
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
	printf("server angle %f\n",e->scene.lights->angle);
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
	char	data[sizeof(t_object) * e->scene.objects_count];

	err = 0;
	//printf("obj covered %d\n", e->scene.objects[0].covered);
	printf("obj has_density %d\n", e->scene.objects[0].has_density);
	//printf("obj[0].center.x %f\n", e->scene.objects[0].center.x);
	//printf("obj[0].center.y %f\n", e->scene.objects[0].center.y);
	//printf("obj[0].center.z %f\n", e->scene.objects[0].center.z);
	//printf("obj[0] angle %f\n", e->scene.objects[0].angle);
	/*
	printf("cam width %f\n", e->camera.width);
	printf("obj name[0] %s\n", e->scene.objects[0].name);
	printf("obj color.r[0] %u\n", e->scene.objects[0].color.r);
	printf("obj color.g[0] %u\n", e->scene.objects[0].color.g);
	printf("obj color.b[0] %u\n", e->scene.objects[0].color.b);
	printf("obj name[1] %s\n", e->scene.objects[1].name);
	printf("obj color.r[1] %u\n", e->scene.objects[1].color.r);
	printf("obj color.g[1] %u\n", e->scene.objects[1].color.g);
	printf("obj color.b[1] %u\n", e->scene.objects[1].color.b);
	printf("obj name[2] %s\n", e->scene.objects[2].name);
	printf("obj color.r[2] %u\n", e->scene.objects[2].color.r);
	printf("obj color.g[2] %u\n", e->scene.objects[2].color.g);
	printf("obj color.b[2] %u\n", e->scene.objects[2].color.b);
	printf("obj name[3] %s\n", e->scene.objects[3].name);
	printf("obj color.r[3] %u\n", e->scene.objects[3].color.r);
	printf("obj color.g[3] %u\n", e->scene.objects[3].color.g);
	printf("obj color.b[3] %u\n", e->scene.objects[3].color.b);
	*/
	err = send(e->srv.socket_cl, &e->srv.id, sizeof(int), 0);
	if (err == SOCKET_ERROR)
	{
		puts("1");
		perror("send()");
		return (err);
	}
	err = send(e->srv.socket_cl, &e->scene.objects_count, sizeof(int), 0);
	if (err == SOCKET_ERROR)
	{
		puts("2");
		perror("send()");
		return (err);
	}
	err = send(e->srv.socket_cl, &e->scene.lights_count, sizeof(int), 0);
	if (err == SOCKET_ERROR)
	{
		puts("3");
		perror("send()");
		return (err);
	}
	//printf("obj center.x %f\n", e->scene.objects->center.x);
	//printf("obj center.y %f\n", e->scene.objects->center.y);
	//printf("obj center.z %f\n", e->scene.objects->center.z);
	printf("server obj->radius %f\n", e->scene.objects[0].radius);
	printf("server obj[1]->radius %f\n", e->scene.objects[1].radius);
	for (int i = 0; i < e->scene.objects_count; i++)
		serialize_obj(&e->scene.objects[i], data);
	float test = atof(&data[5]);
	//printf("server *test %f\n", *test);
	printf("server *data %f\n", test);
	err = send(e->srv.socket_cl, (void *)data,
			sizeof(t_object) * e->scene.objects_count, 0);
	if (err == SOCKET_ERROR)
	{
		puts("4");
		perror("send()");
		return (err);
	}
	err = send(e->srv.socket_cl, e->scene.lights,
			sizeof(t_light) * e->scene.lights_count, 0);
	if (err == SOCKET_ERROR)
	{
		puts("5");
		perror("send()");
		return (err);
	}
	err = send(e->srv.socket_cl, &e->scene, sizeof(t_scene), 0);
	if (err == SOCKET_ERROR)
	{
		puts("6");
		perror("send()");
		return (err);
	}
	err = send(e->srv.socket_cl, &e->camera, sizeof(t_camera), 0);
	if (err == SOCKET_ERROR)
	{
		puts("7");
		perror("send()");
		return (err);
	}
	return (err);
} 
