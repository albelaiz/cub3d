/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:46:42 by yaamaich          #+#    #+#             */
/*   Updated: 2026/03/18 10:07:43 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_walkable(char c)
{
	return (c == '0' || is_player(c));
}

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || is_player(c));
}

static int	has_void_neighbor(t_game *g, int y, int x)
{
	int		cy;
	int		cx;
	char	c;

	cy = y - 1;
	while (cy <= y + 1)
	{
		cx = x - 1;
		while (cx <= x + 1)
		{
			if (!(cy == y && cx == x))
			{
				if (cy < 0 || cx < 0 || cy >= g->map_height || cx >= g->map_width)
					return (1);
				c = g->map[cy][cx];
				if (c == ' ' || c == '\0')
					return (1);
			}
			cx++;
		}
		cy++;
	}
	return (0);
}

static int	check_map_closed(t_game *game)
{
	int	y;
	int	x;
	int	player_count;
	char	c;

	player_count = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			c = game->map[y][x];
			if (!is_valid_map_char(c))
				return (printf("Error\nInvalid character in map\n"), 0);
			if (is_player(c))
				player_count++;
			if (is_walkable(c) && has_void_neighbor(game, y, x))
				return (printf("Error\nMap is not closed around floor/player\n"), 0);
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (printf("Error\nMap must contain exactly one player\n"), 0);
	return (1);
}

static int	check_textures(t_game *game)
{
	if (!game->path_no || !game->path_so
		|| !game->path_we || !game->path_ea)
	{
		printf("Error\nMissing texture paths\n");
		return (0);
	}
	return (1);
}

static int	check_colors(t_game *game)
{
	if (game->color_floor == -1 || game->color_ceiling == -1)
	{
		printf("Error\nMissing colors\n");
		return (0);
	}
	return (1);
}

static int	check_map(t_game *game)
{
	if (!game->map || game->map_height <= 0 || game->map_width <= 0)
	{
		printf("Error\nMissing or invalid map\n");
		return (0);
	}
	if (normalize_map(game) == 0)
		return (0);
	if (!check_map_closed(game))
		return (0);
	return (1);
}

int	validate_all(t_game *game)
{
	if (!check_textures(game))
		return (0);
	if (!check_colors(game))
		return (0);
	if (!check_map(game))
		return (0);
	return (1);
}
