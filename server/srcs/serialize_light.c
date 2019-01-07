/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 09:55:05 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/21 10:15:00 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			serialize_light(t_light *light, char *data)
{
	t_light			*tmp;

	tmp = (t_light *)data;
	*tmp = *light;
	tmp++;
}
