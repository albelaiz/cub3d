/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 02:59:44 by yaamaich          #+#    #+#             */
/*   Updated: 2026/02/22 02:59:48 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double deg_to_rad(double deg)
{
	return (deg * M_PI / 180.0);
}

double rad_to_deg(double rad)
{
	return (rad * 180.0 / M_PI);
}

double norm_deg(double a)
{
	while (a < 0.0)
		a += 360.0;
	while (a >= 360.0)
		a -= 360.0;
	return (a);
}