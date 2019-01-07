/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ocl_init_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 18:14:45 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/21 18:14:49 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void		device_error(const int ret)
{
	if (ret == CL_INVALID_PLATFORM)
		ft_putendl("DEVICE ERROR: CL_INVALID_PLATFORM");
	else if (ret == CL_INVALID_DEVICE_TYPE)
		ft_putendl("DEVICE ERROR: CL_INVALID_DEVICE_TYPE");
	else if (ret == CL_INVALID_VALUE)
		ft_putendl("DEVICE ERROR: CL_INVALID_VALUE");
	else if (ret == CL_DEVICE_NOT_FOUND)
		ft_putendl("DEVICE ERROR: CL_DEVICE_NOT_FOUND");
}

static void		platform_error(const int ret)
{
	if (ret == CL_INVALID_VALUE)
		ft_putendl("PLATFORM ERROR: CL_INVALID_VALUE");
}

static void		program_error(const int ret)
{
	if (ret == CL_INVALID_PROGRAM)
		ft_putendl("PROGRAM ERROR: CL_INVALID_PROGRAM");
	else if (ret == CL_INVALID_VALUE)
		ft_putendl("PROGRAM ERROR: CL_INVALID_VALUE");
	else if (ret == CL_INVALID_VALUE)
		ft_putendl("PROGRAM ERROR: CL_INVALID_VALUE");
	else if (ret == CL_INVALID_DEVICE)
		ft_putendl("PROGRAM ERROR: CL_INVALID_DEVICE");
	else if (ret == CL_INVALID_BINARY)
		ft_putendl("PROGRAM ERROR: CL_INVALID_BINARY");
	else if (ret == CL_INVALID_BUILD_OPTIONS)
		ft_putendl("PROGRAM ERROR: CL_INVALID_BUILD_OPTIONS");
	else if (ret == CL_INVALID_OPERATION)
		ft_putendl("PROGRAM ERROR: CL_INVALID_OPERATION");
	else if (ret == CL_COMPILER_NOT_AVAILABLE)
		ft_putendl("PROGRAM ERROR: CL_COMPILER_NOT_AVAILABLE");
	else if (ret == CL_BUILD_PROGRAM_FAILURE)
		ft_putendl("PROGRAM ERROR: CL_BUILD_PROGRAM_FAILURE");
	else if (ret == CL_INVALID_OPERATION)
		ft_putendl("PROGRAM ERROR: CL_INVALID_OPERATION");
	else if (ret == CL_OUT_OF_RESOURCES)
		ft_putendl("PROGRAM ERROR: CL_OUT_OF_RESOURCES");
	else if (ret == CL_OUT_OF_HOST_MEMORY)
		ft_putendl("PROGRAM ERROR: CL_OUT_OF_HOST_MEMORY");
}

static void		queue_error(const int ret)
{
	if (ret == CL_INVALID_CONTEXT)
		ft_putendl("QUEUE ERROR: CL_INVALID_CONTEXT");
	else if (ret == CL_INVALID_DEVICE)
		ft_putendl("QUEUE ERROR: CL_INVALID_DEVICE");
	else if (ret == CL_INVALID_VALUE)
		ft_putendl("QUEUE ERROR: CL_INVALID_VALUE");
	else if (ret == CL_INVALID_QUEUE_PROPERTIES)
		ft_putendl("QUEUE ERROR: CL_INVALID_QUEUE_PROPERTIES");
	else if (ret == CL_OUT_OF_HOST_MEMORY)
		ft_putendl("QUEUE ERROR: CL_OUT_OF_HOST_MEMORY");
}

void			ft_ocl_init_error(const int ret)
{
	if (ret != 0)
	{
		device_error(ret);
		platform_error(ret);
		program_error(ret);
		queue_error(ret);
	}
	else
		ft_putendl("OK");
}
