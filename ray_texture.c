/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 02:49:40 by yaamaich          #+#    #+#             */
/*   Updated: 2026/02/22 02:49:42 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void set_texx(t_game *g, int tex_w)
{
	if (g->side == 0 && g->ray_dir_x > 0)
		g->texx = tex_w - g->texx - 1;
	if (g->side == 1 && g->ray_dir_y < 0)
		g->texx = tex_w - g->texx - 1;
}

void set_texture(t_game *g, int tex_w)
{
	double	wallx;

	if (g->side == 0)
		wallx = g->player_y + g->perp_wall_dist * g->ray_dir_y;
	else
		wallx = g->player_x + g->perp_wall_dist * g->ray_dir_x;
	wallx -= floor(wallx);

	/* pick texture index based on side + ray sign (same as your code) */
	if (g->side == 0 && g->ray_dir_x > 0)
		g->texnum = 0;
	else if (g->side == 0 && g->ray_dir_x < 0)
		g->texnum = 1;
	else if (g->side == 1 && g->ray_dir_y > 0)
		g->texnum = 2;
	else
		g->texnum = 3;

	g->texx = (int)(wallx * (double)tex_w);
	set_texx(g, tex_w);

	/* recompute perp dist exactly like your sample */
	if (g->side == 0)
		g->perp_wall_dist = (g->map_x - g->player_x
				+ (int)((1 - g->step_x) / 2)) / g->ray_dir_x;
	else
		g->perp_wall_dist = (g->map_y - g->player_y
				+ (int)((1 - g->step_y) / 2)) / g->ray_dir_y;
}