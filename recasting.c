/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelaiz <albelaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 02:50:11 by yaamaich          #+#    #+#             */
/*   Updated: 2026/03/14 12:24:28 by albelaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void render_3d(t_game *g)
{
	int w;
	int x;

	w = (int)g->img_ptr->width;
	draw_background(g);
	x = 0;
	while (x < w)
	{
		cast_and_draw(g, x);
		x++;
	}
}
