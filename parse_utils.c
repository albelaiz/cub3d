/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:47:13 by yaamaich          #+#    #+#             */
/*   Updated: 2026/03/18 10:27:51 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_rgb_array(char **rgb)
{
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
}

void	set_color_type(t_game *game, char type, int col)
{
	if (type == 'F')
		game->color_floor = col;
	else
		game->color_ceiling = col;
}

void	find_player_in_line(t_game *game, char *line)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] == 'N' || line[x] == 'S'
			|| line[x] == 'E' || line[x] == 'W')
		{
			game->player_start_x = x;
			game->player_start_y = game->map_height;
			game->player_start_dir = line[x];
		}
		x++;
	}
}
