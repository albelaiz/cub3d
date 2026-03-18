/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 04:08:13 by yaamaich          #+#    #+#             */
/*   Updated: 2026/03/18 10:25:20 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define TILE 10

void	draw_square(t_game *g, int start_x, int start_y, int size)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;

	if (start_x < 0)
		start_x = 0;
	if (start_y < 0)
		start_y = 0;
	end_x = start_x + size;
	end_y = start_y + size;
	if (end_x > (int)g->img_ptr->width)
		end_x = (int)g->img_ptr->width;
	if (end_y > (int)g->img_ptr->height)
		end_y = (int)g->img_ptr->height;
	y = start_y - 1;
	while (++y < end_y)
	{
		x = start_x;
		while (x < end_x)
		{
			mlx_put_pixel(g->img_ptr, x, y, 0xFF888888);
			x++;
		}
	}
}

static void	draw_tile_row(t_game *g, int y, int x)
{
	char	tile;

	tile = g->map[y][x];
	if (tile == '1')
		draw_square(g, x * TILE, y * TILE, TILE);
	else if (tile == '0')
		mlx_put_pixel(g->img_ptr, x * TILE, y * TILE, 0xFF000000);
	else
		mlx_put_pixel(g->img_ptr, x * TILE, y * TILE, 0xFF202020);
}

void	draw_map(t_game *g)
{
	int	y;
	int	x;

	y = 0;
	while (y < g->map_height)
	{
		x = 0;
		while (x < g->map_width)
		{
			draw_tile_row(g, y, x);
			x++;
		}
		y++;
	}
}

void	draw_player(t_game *g)
{
	int	px;
	int	py;

	px = (int)(g->player_x * TILE);
	py = (int)(g->player_y * TILE);
	draw_square(g, px - 3, py - 3, 6);
}

void	clear_image(mlx_image_t *img, uint32_t color)
{
	uint32_t	y;
	uint32_t	x;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
