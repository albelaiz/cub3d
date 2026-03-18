/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting_tex_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:38:47 by yaamaich          #+#    #+#             */
/*   Updated: 2026/03/18 09:39:04 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	clamp_tx(mlx_texture_t *tex, int tx)
{
	if (tx < 0)
		tx = 0;
	if (tx >= (int)tex->width)
		tx = (int)tex->width - 1;
	return (tx);
}

static int	get_draw_start(int line_h, int h)
{
	int	draw_start;

	draw_start = -line_h / 2 + h / 2;
	if (draw_start < 0)
		draw_start = 0;
	return (draw_start);
}

void	draw_textured_vline(t_game *g, int x, t_ray *r, double perp)
{
	mlx_texture_t	*tex;
	int				h;
	int				line_h;
	int				draw_end;
	int				tx;
	int				ty;
	int				y;

	tex = get_wall_texture(g, r);
	h = (int)g->img_ptr->height;
	line_h = (int)(h / perp);
	draw_end = line_h / 2 + h / 2;
	tx = (int)(r->wall_x * (double)tex->width);
	tx = clamp_tx(tex, tx);
	y = get_draw_start(line_h, h);
	while (y <= draw_end && y < h)
	{
		ty = (int)(((y - (-line_h / 2 + h / 2)) * tex->height)
			/ (double)line_h);
		mlx_put_pixel(g->img_ptr, x, y, get_tex_pixel(tex, tx, ty));
		y++;
	}
}