/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 16:50:04 by aabelque          #+#    #+#             */
/*   Updated: 2019/02/16 16:50:07 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void				set_opencl_env(t_env *env, t_opencl *opcl)
{
	opcl->dev_type = CL_DEVICE_TYPE_CPU;
	opcl->err = 0;
	opcl->platform_id = NULL;
	opcl->device_id = 0;
	opcl->context = NULL;
	opcl->commands = NULL;
	opcl->program = NULL;
	opcl->kernel_src = NULL;
	opcl->input_scene = NULL;
	opcl->input_cam = NULL;
	opcl->structobj = NULL;
	opcl->output = NULL;
	opcl->imgxy[0] = env->win_width;
	opcl->imgxy[1] = env->win_height;
	opcl->kernel = NULL;
	opcl->origin[0] = env->win_width;
	opcl->origin[1] = env->win_height;
	opcl->origin[2] = 1;
	ft_bzero(opcl->region, sizeof(size_t) * 3);
}

void				create_kernel(cl_program program, cl_kernel *kernel,
		const char *func)
{
	cl_int			err;

	if (!(*kernel = clCreateKernel(program, func, &err)) || err != CL_SUCCESS)
	{
		ft_putendl("Error: Failed to create kernel");
		exit(EXIT_FAILURE);
	}
}

char				*get_kernel_source(char *file)
{
	char			*kernel_src;
	struct stat		stats;
	int				fd;

	if (stat(file, &stats) == -1)
	{
		ft_putendl("Error: kernel source not found");
		exit(EXIT_FAILURE);
	}
	if (!(fd = open(file, O_RDONLY)))
	{
		ft_putendl("Error: fail to load kernel source");
		exit(EXIT_FAILURE);
	}
	kernel_src = ft_memalloc(stats.st_size);
	read(fd, kernel_src, stats.st_size);
	close(fd);
	return (kernel_src);
}

void				create_prog(t_opencl *opcl)
{
	cl_int			error;
	size_t			file_length;

	file_length = file_len(open("./client/srcs/raytracer.cl", O_RDONLY));
	opcl->kernel_src = get_kernel_source("./client/srcs/raytracer.cl");
	if (!(opcl->program = clCreateProgramWithSource(opcl->context, 1,
					(const char **)&opcl->kernel_src,
					(const size_t *)&file_length, &opcl->err))
			|| opcl->err != CL_SUCCESS)
	{
		ft_putendl("Error: Failed to create program with source");
		exit(EXIT_FAILURE);
	}
	error = clBuildProgram(opcl->program, 1, &opcl->device_id,
				NULL, NULL, NULL);
	error_gpu(opcl);
	free((void *)opcl->kernel_src);
}

void				opencl_init(t_opencl *opcl, t_env *env)
{
	if (clGetPlatformIDs(1, &opcl->platform_id, NULL) != CL_SUCCESS)
	{
		ft_putendl("Error: Failed to get a platformID");
		exit(EXIT_FAILURE);
	}
	if (clGetDeviceIDs(opcl->platform_id, opcl->dev_type, 1,
			&opcl->device_id, NULL) != CL_SUCCESS)
	{
		ft_putendl("Error: Failed to create deviceID group");
		exit(EXIT_FAILURE);
	}
	if (!(opcl->context = clCreateContext(NULL, 1, &opcl->device_id, NULL, NULL,
			&opcl->err)))
	{
		ft_putendl("Error: Failed to create a context");
		exit(EXIT_FAILURE);
	}
	if (!(opcl->commands = clCreateCommandQueue(opcl->context, opcl->device_id,
			0, &opcl->err)))
	{
		ft_putendl("Error: Failed to create command queue");
		exit(EXIT_FAILURE);
	}
	opencl_init2(opcl, env);
}
