/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 03:45:25 by yaamaich          #+#    #+#             */
/*   Updated: 2026/02/28 12:13:39 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static int	cell_blocks(t_game *g, int mx, int my)
{
	if (mx < 0 || my < 0 || mx >= g->map_width || my >= g->map_height)
		return (1);
	return (g->map[my][mx] == '1' || g->map[my][mx] == ' ');
}

static int	position_blocks(t_game *g, double wx, double wy)
{
	// "radius" so you don't clip corners; tweak 0.15..0.25
	const double r = 0.20;

	int left   = (int)(wx - r);
	int right  = (int)(wx + r);
	int top    = (int)(wy - r);
	int bottom = (int)(wy + r);

	if (cell_blocks(g, left, top)) return (1);
	if (cell_blocks(g, right, top)) return (1);
	if (cell_blocks(g, left, bottom)) return (1);
	if (cell_blocks(g, right, bottom)) return (1);
	return (0);
}

static void	apply_motion(t_game *g, double vx, double vy)
{
	double nx = g->player_x + vx;
	double ny = g->player_y + vy;

	// separated axis => smoother along walls
	if (!position_blocks(g, nx, g->player_y))
		g->player_x = nx;
	if (!position_blocks(g, g->player_x, ny))
		g->player_y = ny;
}

void	handle_player_input(t_game *g)
{
	const double step = 0.04;
	const double turn = 0.03;

	// facing direction
	double fx = cos(g->player_dir);
	double fy = sin(g->player_dir);

	// right vector (perpendicular)
	double rx = -fy;
	double ry = fx;

	if (mlx_is_key_down(g->mlx_ptr, MLX_KEY_W))
		apply_motion(g, fx * step, fy * step);
	if (mlx_is_key_down(g->mlx_ptr, MLX_KEY_S))
		apply_motion(g, -fx * step, -fy * step);
	if (mlx_is_key_down(g->mlx_ptr, MLX_KEY_D))
		apply_motion(g, rx * step, ry * step);
	if (mlx_is_key_down(g->mlx_ptr, MLX_KEY_A))
		apply_motion(g, -rx * step, -ry * step);

	if (mlx_is_key_down(g->mlx_ptr, MLX_KEY_LEFT))
		g->player_dir -= turn;
	if (mlx_is_key_down(g->mlx_ptr, MLX_KEY_RIGHT))
		g->player_dir += turn;

	if (mlx_is_key_down(g->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(g->mlx_ptr);
}