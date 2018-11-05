/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:30:12 by aabelque          #+#    #+#             */
/*   Updated: 2018/11/05 18:41:34 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				set_opencl_env(t_opencl *opcl)
{
	opcl->dev_type = CL_DEVICE_TYPE_GPU;
	opcl->err = 0;
	opcl->platform_id = NULL;
	opcl->device_id = 0;
	opcl->context = NULL;
	opcl->commands = NULL;
	opcl->program = NULL;
	opcl->kernel_src = NULL;
	opcl->dataobj = NULL;
	opcl->datascene = NULL;
	opcl->datalight = NULL;
	opcl->datacam = NULL;
	opcl->memobj = NULL;
	opcl->imgxy[0] = WIN_WIDTH;
	opcl->imgxy[1] = WIN_HEIGHT;
	opcl->kernel = NULL;
	printf("addr 1 = %p\n", opcl->dataobj);
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

	file_length = file_len(open("./srcs/raytracer.cl", O_RDONLY));
	opcl->kernel_src = get_kernel_source("./srcs/raytracer.cl");
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
