/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ocl_kernel_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 18:15:00 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/21 18:15:03 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void		invalid_object_sampler(const int ret)
{
	if (ret == CL_INVALID_MEM_OBJECT)
	{
		ft_putendl("CL_INVALID_MEM_OBJECT:");
		ft_putstr("an argument is declared to be a memory object when the ");
		ft_putendl("specified arg_value is not a valid memory object.");
	}
	else if (ret == CL_INVALID_SAMPLER)
	{
		ft_putendl("CL_INVALID_SAMPLER:");
		ft_putstr("an argument declared to be of type sampler_t when the ");
		ft_putendl("specified arg_value is not a valid sampler object.");
	}
}

static void		invalid_arg(const int ret)
{
	if (ret == CL_INVALID_ARG_INDEX)
	{
		ft_putendl("CL_INVALID_ARG_INDEX:");
		ft_putendl("arg_index is not a valid argument index.");
	}
	else if (ret == CL_INVALID_ARG_VALUE)
	{
		ft_putendl("CL_INVALID_ARG_VALUE:");
		ft_putstr("arg_value specified is NULL for an argument that is not ");
		ft_putendl("declared with the __local qualifier or vice-versa.");
	}
	else if (ret == CL_INVALID_ARG_SIZE)
	{
		ft_putendl("CL_INVALID_ARG_SIZE:");
		ft_putstr("arg_size does not match the size of the data type for an ");
		ft_putendl("argument that is not a memory object \nor");
		ft_putstr("the argument is a memory object and arg_size !=");
		ft_putendl("sizeof(cl_mem) \nor");
		ft_putstr("arg_size is zero and the argument is declared with the ");
		ft_putendl("__local qualifier \nor");
		ft_putstr("the argument is a sampler and arg_size ");
		ft_putendl("!= sizeof(cl_sampler).");
	}
}

static void		invalid_out(const int ret)
{
	if (ret == CL_OUT_OF_RESOURCES)
	{
		ft_putendl("CL_OUT_OF_RESOURCES:");
		ft_putstr("there is a failure to allocate resources required by the ");
		ft_putstr("OpenCL implementation on the device.");
	}
	else if (ret == CL_OUT_OF_HOST_MEMORY)
	{
		ft_putendl("CL_OUT_OF_HOST_MEMORY:");
		ft_putstr("there is a failure to allocate resources required by the ");
		ft_putstr("OpenCL implementation on the host.");
	}
}

void			ft_ocl_kernel_error(const int ret, const size_t index)
{
	if (ret == CL_INVALID_KERNEL)
	{
		ft_putendl("CL_INVALID_KERNEL:");
		ft_putendl("kernel is not a valid kernel object.");
		ft_putstr("ERROR ARG - ");
		ft_putnbr(index);
		ft_putendl(":");
		invalid_arg(ret);
		invalid_object_sampler(ret);
		invalid_out(ret);
	}
}
