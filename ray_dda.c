/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 02:49:09 by yaamaich          #+#    #+#             */
/*   Updated: 2026/02/22 03:04:44 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void set_delta(t_game *g)
{
	if (g->ray_dir_x == 0.0)
		g->delta_dist_x = 1e30;
	else
		g->delta_dist_x = fabs(1.0 / g->ray_dir_x);
	if (g->ray_dir_y == 0.0)
		g->delta_dist_y = 1e30;
	else
		g->delta_dist_y = fabs(1.0 / g->ray_dir_y);
}

void set_side_dist(t_game *g)
{
	if (g->ray_dir_x < 0)
	{
		g->step_x = -1;
		g->side_dist_x = (g->player_x - g->map_x) * g->delta_dist_x;
	}
	else
	{
		g->step_x = 1;
		g->side_dist_x = (g->map_x + 1.0 - g->player_x) * g->delta_dist_x;
	}
	if (g->ray_dir_y < 0)
	{
		g->step_y = -1;
		g->side_dist_y = (g->player_y - g->map_y) * g->delta_dist_y;
	}
	else
	{
		g->step_y = 1;
		g->side_dist_y = (g->map_y + 1.0 - g->player_y) * g->delta_dist_y;
	}
}

int finding_hit(t_game *g)
{
	g->hit = 0;
	while (!g->hit)
	{
		if (g->side_dist_x < g->side_dist_y)
		{
			g->side_dist_x += g->delta_dist_x;
			g->map_x += g->step_x;
			g->side = 0;
		}
		else
		{
			g->side_dist_y += g->delta_dist_y;
			g->map_y += g->step_y;
			g->side = 1;
		}
		if (g->map_x < 0 || g->map_y < 0
			|| g->map_x >= g->map_width || g->map_y >= g->map_height)
			return (0);
		if (g->map[g->map_y][g->map_x] == '1')
			g->hit = 1;
	}
	return (1);
}