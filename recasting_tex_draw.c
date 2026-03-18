/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting_tex_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:38:47 by yaamaich          #+#    #+#             */
/*   Updated: 2026/03/18 10:32:01 by yaamaich         ###   ########.fr       */
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

static int	get_ty(int y, int line_h, int h, mlx_texture_t *tex)
{
	return ((int)(((y - (-line_h / 2 + h / 2)) * tex->height)
		/ (double)line_h));
}

void	draw_textured_vline(t_game *g, int x, t_ray *r, double perp)
{
	mlx_texture_t	*tex;
	int				h;
	int				line_h;
	int				y;
	int				draw_end;

	tex = get_wall_texture(g, r);
	h = (int)g->img_ptr->height;
	line_h = (int)(h / perp);
	draw_end = line_h / 2 + h / 2;
	y = get_draw_start(line_h, h);
	while (y <= draw_end && y < h)
	{
		mlx_put_pixel(g->img_ptr, x, y,
			get_tex_pixel(tex,
				clamp_tx(tex, (int)(r->wall_x * (double)tex->width)),
				get_ty(y, line_h, h, tex)));
		y++;
	}
}
