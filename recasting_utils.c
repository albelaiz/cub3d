/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelaiz <albelaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:45:10 by yaamaich          #+#    #+#             */
/*   Updated: 2026/03/14 12:24:22 by albelaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void draw_background(t_game *g)
{
	int w;
	int h;
	int x;
	int y;

	w = (int)g->img_ptr->width;
	h = (int)g->img_ptr->height;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (y < h / 2)
				mlx_put_pixel(g->img_ptr, x, y, 0x00BFFFFF);
			else
				mlx_put_pixel(g->img_ptr, x, y, 0x808080FF);
			x++;
		}
		y++;
	}
}

void draw_vline(t_game *g, int x, int y0, int y1, uint32_t color)
{
	if (y0 < 0)
		y0 = 0;
	if (y1 >= (int)g->img_ptr->height)
		y1 = (int)g->img_ptr->height - 1;
	while (y0 <= y1)
	{
		mlx_put_pixel(g->img_ptr, x, y0, color);
		y0++;
	}
}
