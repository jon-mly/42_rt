/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 16:42:08 by aabelque          #+#    #+#             */
/*   Updated: 2018/08/18 17:06:30 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void		opencl_free(t_opencl *opcl)
{
	clReleaseProgram(opcl->program);
	clReleaseKernel(opcl->kernel);
	clReleaseMemObject(opcl->input_scene);
	clReleaseMemObject(opcl->input_cam);
	clReleaseMemObject(opcl->output);
	clReleaseMemObject(opcl->structobj);
	clReleaseMemObject(opcl->structlight);
	clReleaseCommandQueue(opcl->commands);
	clReleaseContext(opcl->context);
}
