/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:40:56 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/19 16:15:56 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static	int		parse_arg(t_env *e, char *av, char *av2)
{
	if (ft_strequ(av, "-p"))
	{
		if (ft_atoi(av2) >= 0 && ft_atoi(av2) <= 1024)
			exit_usage();
		else
			e->srv.port = ft_atoi(av2);
	}
	return (1);
}

void		await_data(t_env *env)
{
	env->srv.cl_state = WAIT_DATA;
	recv_obj_light(env);
}

void		perform_rendering(t_env *env)
{
	env->srv.cl_state = RENDERING;
	opencl_init(&env->opcl, env);
	opencl_draw(&env->opcl, env);
}

void		send_rendering(t_env *env)
{
	int	err;
	env->srv.cl_state = SENDING;
	if ((mlx_put_image_to_window(env->mlx_ptr, env->win_ptr,
					env->img_ptr, 0, 0)) == -1)
		ft_putendl("Failed to put image to window");
	int size = sizeof(char) * WIN_WIDTH * WIN_HEIGHT * 4;
	char *tmp = env->img_str;
	while (size > 0)
	{
		if ((err = send(env->srv.socket, tmp, (int)fmin(1024, size), 0)) < 0)
		{
			perror("send()");
			exit(EXIT_FAILURE);
		}
		// printf("Sent : %12d - remaining : %12d\n", err, size);
		size -= err;
		tmp += err;
	}
	ft_putendl("HAS TERMINATED SENDING");
}

void		*loop_client_lifecycle(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	//while (1)
	//{
		await_data(env);
		perform_rendering(env);
		send_rendering(env);
	//}
	return (NULL);
}

int			main(int ac, char **av)
{
	t_env	*env;

	if (ac != 4)
		exit_usage2();
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		exit(EXIT_FAILURE);
	parse_arg(env, av[2], av[3]);
	env = init_env2();
	init_env_client(env, av[1]);
	create_client(env);
	mlx_hook(env->win_ptr, 2, 0, handle_key_event, (void*)env);
	mlx_hook(env->win_ptr, 17, 0, exit_properly, (void*)env);
	mlx_loop_hook(env->mlx_ptr, expose_event, (void*)env);
	set_opencl_env(&env->opcl);
	if (pthread_create(&(env->thr), NULL, loop_client_lifecycle, env))
	{
		ft_putendl("Error launching client lifecycle : pthread_create");
		exit(EXIT_FAILURE);
	}
	if (pthread_join(env->thr, NULL))
	{
		ft_putendl("Error launching client lifecycle : pthread_join");
		exit(EXIT_FAILURE);
	}
	mlx_loop(env->mlx_ptr);
	return (0);
}
