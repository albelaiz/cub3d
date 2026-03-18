/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 01:44:03 by yaamaich          #+#    #+#             */
/*   Updated: 2026/03/18 09:35:14 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

double	deg_to_rad(double deg)
{
	return (deg * M_PI / 180.0);
}

double	rad_to_deg(double rad)
{
	return (rad * 180.0 / M_PI);
}

double	norm_deg(double a)
{
	while (a < 0.0)
		a += 360.0;
	while (a >= 360.0)
		a -= 360.0;
	return (a);
}

static void	set_player_direction(t_game *g, char c)
{
	if (c == 'S')
		g->player_dir = deg_to_rad(90);
	else if (c == 'N')
		g->player_dir = deg_to_rad(270);
	else if (c == 'E')
		g->player_dir = deg_to_rad(0);
	else if (c == 'W')
		g->player_dir = deg_to_rad(180);
}

void	init_player(t_game *g)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (g->map && g->map[y])
	{
		x = 0;
		while (g->map[y][x])
		{
			c = g->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				g->player_x = x + 0.5;
				g->player_y = y + 0.5;
				set_player_direction(g, c);
				g->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
