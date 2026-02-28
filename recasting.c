/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 02:50:11 by yaamaich          #+#    #+#             */
/*   Updated: 2026/02/28 12:04:32 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	render_3d(t_game *g)
{
	int	w;
	int	x;

	w = (int)g->img_ptr->width;
	draw_background(g);
	x = 0;
	while (x < w)
	{
		cast_and_draw(g, x);
		x++;
	}
}
