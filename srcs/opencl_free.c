/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 16:42:08 by aabelque          #+#    #+#             */
/*   Updated: 2018/11/05 13:42:09 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		opencl_free(t_opencl *opcl)
{
	clReleaseProgram(opcl->program);
	clReleaseKernel(opcl->kernel);
	clReleaseMemObject(*opcl->memobj);
	clReleaseCommandQueue(opcl->commands);
	clReleaseContext(opcl->context);
}
