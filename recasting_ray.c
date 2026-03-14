/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelaiz <albelaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:29:06 by yaamaich          #+#    #+#             */
/*   Updated: 2026/03/14 12:24:04 by albelaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void init_ray(t_game *g, int x, t_ray *r)
{
	double fov;
	double plane_len;

	fov = M_PI / 3.0;
	plane_len = tan(fov / 2.0);
	r->dir_x = cos(g->player_dir);
	r->dir_y = sin(g->player_dir);
	r->plane_x = -r->dir_y * plane_len;
	r->plane_y = r->dir_x * plane_len;
	r->cam_x = 2.0 * x / (double)g->img_ptr->width - 1.0;
	r->ray_dir_x = r->dir_x + r->plane_x * r->cam_x;
	r->ray_dir_y = r->dir_y + r->plane_y * r->cam_x;
	r->map_x = (int)g->player_x;
	r->map_y = (int)g->player_y;
	if (r->ray_dir_x == 0)
		r->delta_x = 1e30;
	else
		r->delta_x = fabs(1.0 / r->ray_dir_x);
	if (r->ray_dir_y == 0)
		r->delta_y = 1e30;
	else
		r->delta_y = fabs(1.0 / r->ray_dir_y);
}

void setup_steps(t_game *g, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_x = (g->player_x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0 - g->player_x) * r->delta_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_y = (g->player_y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0 - g->player_y) * r->delta_y;
	}
}

int dda_loop(t_game *g, t_ray *r)
{
	int hit;

	hit = 0;
	r->side = 0;
	while (!hit)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x < 0 || r->map_y < 0 || r->map_x >= g->map_width || r->map_y >= g->map_height)
			return (0);
		if (g->map[r->map_y][r->map_x] == '1')
			hit = 1;
	}
	return (1);
}

void cast_and_draw(t_game *g, int x)
{
	t_ray r;
	double perp;

	init_ray(g, x, &r);
	setup_steps(g, &r);
	if (!dda_loop(g, &r))
		return;
	if (r.side == 0)
	{
		perp = (r.map_x - g->player_x + (1 - r.step_x) / 2.0) / r.ray_dir_x;
		r.wall_x = g->player_y + perp * r.ray_dir_y;
	}
	else
	{
		perp = (r.map_y - g->player_y + (1 - r.step_y) / 2.0) / r.ray_dir_y;
		r.wall_x = g->player_x + perp * r.ray_dir_x;
	}
	if (perp <= 0.0001)
		perp = 0.0001;
	r.wall_x -= floor(r.wall_x);
	draw_textured_vline(g, x, &r, perp);
}
