/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:07:23 by aabelque          #+#    #+#             */
/*   Updated: 2018/11/05 13:42:26 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	opencl_init2(t_opencl *opcl, t_env *e)
{
	opcl->img_s = WIN_WIDTH * WIN_HEIGHT;
	if ((opcl->memobj = (cl_mem *)malloc(sizeof(cl_mem) * 5)) == NULL)
	{
		ft_putendl("Error: fail to alloc memobj");
		exit(EXIT_FAILURE);
	}
	opcl->memobj[0] = clCreateBuffer(opcl->context,
			CL_MEM_READ_WRITE,
			sizeof(int) * opcl->img_s, NULL, &opcl->err);
	printf("err 0 = %d\n", opcl->err);
	opcl->memobj[1] = clCreateBuffer(opcl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_object) * e->scene.objects_count, e->scene.objects, &opcl->err);
	printf("err 1 = %d\n", opcl->err);
	opcl->memobj[2] = clCreateBuffer(opcl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_light) * e->scene.lights_count, e->scene.lights, &opcl->err);
	printf("err 2 = %d\n", opcl->err);
	opcl->memobj[3] = clCreateBuffer(opcl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_scene), &e->scene, &opcl->err);
	printf("err 3 = %d\n", opcl->err);
	opcl->memobj[4] = clCreateBuffer(opcl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_camera), &e->camera, &opcl->err);
	printf("err 4 = %d\n", opcl->err);

	opcl->err = 0;
	opcl->dataimg = (int *)clEnqueueMapBuffer(opcl->commands,
			opcl->memobj[0], CL_TRUE, CL_MAP_WRITE, 0, sizeof(int) * opcl->img_s,
			0, NULL, NULL, &opcl->err);
	printf("errimg = %d\n", opcl->err);
	opcl->dataobj = (t_object *)clEnqueueMapBuffer(opcl->commands,
			opcl->memobj[1], CL_TRUE, CL_MAP_READ, 0, sizeof(t_object)
			* e->scene.objects_count, 0, NULL, NULL, &opcl->err); 
	printf("errobj = %d\n", opcl->err);
	opcl->datalight = (t_light *)clEnqueueMapBuffer(opcl->commands,
			opcl->memobj[2], CL_TRUE, CL_MAP_READ, 0, sizeof(t_light)
			* e->scene.lights_count, 0, NULL, NULL, &opcl->err); 
	printf("errlight = %d\n", opcl->err);
	opcl->datascene = (t_scene *)clEnqueueMapBuffer(opcl->commands,
			opcl->memobj[3], CL_TRUE, CL_MAP_READ, 0, sizeof(t_scene),
			0, NULL, NULL, &opcl->err); 
	printf("errscene = %d\n", opcl->err);
	opcl->datacam = (t_camera *)clEnqueueMapBuffer(opcl->commands,
			opcl->memobj[4], CL_TRUE, CL_MAP_READ, 0, sizeof(t_camera),
			0, NULL, NULL, &opcl->err); 
	printf("errcam = %d\n", opcl->err);

	printf("addr = %p\n", opcl->dataobj);
	ft_memmove((void *)opcl->dataobj, (void *)e->scene.objects,
			sizeof(t_object) * e->scene.objects_count);
	ft_memmove(opcl->datalight, e->scene.lights,
			sizeof(t_light) * e->scene.lights_count);
	ft_memmove(opcl->datascene, &e->scene, sizeof(t_scene));
	ft_memmove(opcl->datacam, &e->camera, sizeof(t_camera));
	ft_memmove(opcl->dataimg, e->img_str, sizeof(int) * opcl->img_s);
	printf("count obj = %d\n", opcl->datascene->objects_count);
	
	create_prog(opcl);
	create_kernel(opcl->program, &opcl->kernel, "pixel_raytracing_gpu");
}
