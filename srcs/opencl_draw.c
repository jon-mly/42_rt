/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:58:44 by aabelque          #+#    #+#             */
/*   Updated: 2018/11/05 13:42:02 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			opencl_draw(t_opencl *opcl, t_env *e)
{
	opcl->err = clEnqueueWriteBuffer(opcl->commands, opcl->memobj[1],
			CL_FALSE, 0, sizeof(t_object) * e->scene.objects_count,
			opcl->dataobj, 0, NULL, NULL);
	printf("error enqueue buffer obj: %d\n", opcl->err);
	
	opcl->err = clEnqueueWriteBuffer(opcl->commands, opcl->memobj[2],
			CL_FALSE, 0, sizeof(t_light) * e->scene.lights_count,
			opcl->datalight, 0, NULL, NULL);
	printf("error enqueue buffer light: %d\n", opcl->err);
	
	opcl->err = clEnqueueWriteBuffer(opcl->commands, opcl->memobj[3],
			CL_FALSE, 0, sizeof(t_scene), &opcl->datascene, 0, NULL, NULL);
	printf("error enqueue buffer scene: %d\n", opcl->err);
	
	opcl->err = clEnqueueWriteBuffer(opcl->commands, opcl->memobj[4],
			CL_FALSE, 0, sizeof(t_camera), &opcl->datacam, 0, NULL, NULL);
	printf("error enqueue buffer camera: %d\n", opcl->err);
	
	opcl->err = clSetKernelArg(opcl->kernel, 0, sizeof(cl_mem),
			(void *)&opcl->memobj[0]);
	printf("error set kernel 0: %d\n", opcl->err);
	
	opcl->err |= clSetKernelArg(opcl->kernel, 1, sizeof(cl_mem),
			(void *)&opcl->memobj[1]);
	printf("error set kernel 1: %d\n", opcl->err);
	
	opcl->err |= clSetKernelArg(opcl->kernel, 2, sizeof(cl_mem),
			(void *)&opcl->memobj[2]);
	printf("error set kernel 2: %d\n", opcl->err);
	
	opcl->err |= clSetKernelArg(opcl->kernel, 3, sizeof(cl_mem),
			(void *)&opcl->memobj[3]);
	printf("error set kernel 3: %d\n", opcl->err);
	
	opcl->err |= clSetKernelArg(opcl->kernel, 4, sizeof(cl_mem),
			(void *)&opcl->memobj[4]);
	printf("error set kernel 4: %d\n", opcl->err);

	opcl->err = clEnqueueNDRangeKernel(opcl->commands, opcl->kernel,
			2, NULL, opcl->imgxy, NULL, 0, NULL, NULL);
	printf("error NDrange: %d\n", opcl->err);

	opcl->err = clEnqueueReadBuffer(opcl->commands, opcl->memobj[0], CL_TRUE, 0,
			sizeof(int) * opcl->img_s, e->img_str, 0, NULL, NULL);
	printf("error Read Buffer: %d\n", opcl->err);
}
