/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:27:48 by aabelque          #+#    #+#             */
/*   Updated: 2018/11/05 13:43:02 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector			shape_normal(t_object ray, t_object object)
{
	if (object.typpe == SPHERE)
		return (sphere_normal(ray, object));
	else if (object.typpe == PLANE)
		return (plane_normal(ray, object));
	else if (object.typpe == CYLINDER)
		return (cylinder_normal(ray, object));
	else
		return (cone_normal(ray, object));
}
