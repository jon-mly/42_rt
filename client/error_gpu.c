/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_gpu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:56:42 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/10 16:27:00 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int			error_gpu(t_opencl *opcl)
{
	char	*errbuf;
	cl_int	coderr;
	size_t	errlog;

	if (clBuildProgram(opcl->program, 1, &opcl->device_id,
				NULL, NULL, NULL) != CL_SUCCESS)
	{
		coderr = clGetProgramBuildInfo(opcl->program, opcl->device_id,
				CL_PROGRAM_BUILD_LOG, 0, NULL, &errlog);
		errbuf = ft_memalloc(sizeof(errlog));
		coderr = clGetProgramBuildInfo(opcl->program, opcl->device_id,
				CL_PROGRAM_BUILD_LOG, errlog, errbuf, NULL);
		ft_putendl("Error: Failed to build program");
		ft_putendl(errbuf);
		exit(EXIT_FAILURE);
	}
	return (0);
}
