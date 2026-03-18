/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting_tex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:02:27 by yaamaich          #+#    #+#             */
/*   Updated: 2026/03/18 09:38:10 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_textures(t_game *g)
{
	g->tex_no = mlx_load_png(g->path_no);
	g->tex_so = mlx_load_png(g->path_so);
	g->tex_we = mlx_load_png(g->path_we);
	g->tex_ea = mlx_load_png(g->path_ea);
	if (!g->tex_no || !g->tex_so || !g->tex_we || !g->tex_ea)
	{
		printf("Error\nFailed to load texture\n");
		return (0);
	}
	return (1);
}

uint32_t	get_tex_pixel(mlx_texture_t *tex, int tx, int ty)
{
	uint8_t	*pixel;
	int		index;

	if (tx < 0)
		tx = 0;
	if (ty < 0)
		ty = 0;
	if (tx >= (int)tex->width)
		tx = (int)tex->width - 1;
	if (ty >= (int)tex->height)
		ty = (int)tex->height - 1;
	index = (ty * (int)tex->width + tx) * 4;
	pixel = tex->pixels;
	return ((pixel[index] << 24) | (pixel[index + 1] << 16)
		| (pixel[index + 2] << 8) | pixel[index + 3]);
}

mlx_texture_t	*get_wall_texture(t_game *g, t_ray *r)
{
	if (r->side == 1 && r->step_y > 0)
		return (g->tex_no);
	if (r->side == 1 && r->step_y < 0)
		return (g->tex_so);
	if (r->side == 0 && r->step_x > 0)
		return (g->tex_ea);
	return (g->tex_we);
}
