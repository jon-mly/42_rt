/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 16:50:16 by aabelque          #+#    #+#             */
/*   Updated: 2019/02/16 16:50:18 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	opencl_init2(t_opencl *opcl, t_env *e)
{
	opcl->img_s = e->win_width * e->win_height;
	opcl->format = (cl_image_format){.image_channel_order = CL_RGBA,
		.image_channel_data_type = CL_UNSIGNED_INT8};
	opcl->desc = (cl_image_desc){.image_type = CL_MEM_OBJECT_IMAGE2D,
		.image_width = e->win_width, .image_height = e->win_height,
		.image_depth = 1, .image_array_size = 0,
		.image_row_pitch = 0, .image_slice_pitch = 0,
		.num_mip_levels = 0, .num_samples = 0, .buffer = NULL};
	opcl->output = clCreateImage(opcl->context,
			CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR, &opcl->format,
			&opcl->desc, NULL, &opcl->err);
	opcl->structobj = clCreateBuffer(opcl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_object) * e->scene.objects_count, e->scene.objects, NULL);
	opcl->structlight = clCreateBuffer(opcl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_light) * e->scene.lights_count, e->scene.lights, NULL);
	opcl->input_scene = clCreateBuffer(opcl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_scene), &e->scene, NULL);
	opcl->input_cam = clCreateBuffer(opcl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_camera), &e->camera, NULL);
	create_prog(opcl);
	create_kernel(opcl->program, &opcl->kernel, "pixel_raytracing_gpu");
}
