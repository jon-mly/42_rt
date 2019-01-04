/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 17:43:51 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/12/21 10:15:29 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			is_empty(char *line)
{
	int		i;

	i = -1;
	if (!line)
		return (1);
	while (line[++i] != '\0')
	{
		if (line[i] != '\n' && line[i] != '\0' && line[i] != ' '
				&& line[i] != '\t' && line[i] != '\v' && line[i] != '\r')
			return (0);
	}
	return (1);
}

int			hit_test(t_object *clt_obj, t_object *obj, t_object l_ray,
		float norm)
{
	if (!(l_ray.intersect && l_ray.norm > 0))
		return (0);
	if (clt_obj == obj)
		return (l_ray.norm < norm - 0.1);
	return (l_ray.norm < norm);
}
