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

static void	free_visited(char **visited, int height)
{
	int	i;

	i = 0;
	if (!visited)
		return ;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

static char	**alloc_visited(t_game *g)
{
	char	**visited;
	int		y;

	visited = (char **)malloc(sizeof(char *) * g->map_height);
	if (!visited)
		return (NULL);
	y = 0;
	while (y < g->map_height)
	{
		visited[y] = (char *)ft_calloc(g->map_width, sizeof(char));
		if (!visited[y])
		{
			free_visited(visited, y);
			return (NULL);
		}
		y++;
	}
	return (visited);
}

static int	flood_fill_region(t_game *g, char **visited, int y, int x)
{
	int			i;
	int			dir_y[4];
	int			dir_x[4];
	char		c;

	if (y < 0 || x < 0 || y >= g->map_height || x >= g->map_width)
		return (0);
	c = g->map[y][x];
	if (c == ' ' || c == '\0')
		return (0);
	if (c == '1')
		return (1);
	if (visited[y][x])
		return (1);
	visited[y][x] = 1;
	dir_y[0] = -1;
	dir_y[1] = 1;
	dir_y[2] = 0;
	dir_y[3] = 0;
	dir_x[0] = 0;
	dir_x[1] = 0;
	dir_x[2] = -1;
	dir_x[3] = 1;
	i = 0;
	while (i < 4)
	{
		if (!flood_fill_region(g, visited, y + dir_y[i], x + dir_x[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_map_closed(t_game *game)
{
	char	**visited;
	int	y;
	int	x;
	int	player_count;
	char	c;

	visited = alloc_visited(game);
	if (!visited)
		return (printf("Error\nMalloc failed\n"), 0);
	player_count = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			c = game->map[y][x];
			if (!is_valid_map_char(c))
				return (free_visited(visited, game->map_height),
					printf("Error\nInvalid character in map\n"), 0);
			if (is_player(c))
				player_count++;
			if (is_walkable(c) && !visited[y][x]
				&& !flood_fill_region(game, visited, y, x))
				return (free_visited(visited, game->map_height),
					printf("Error\nMap is not closed around floor/player\n"), 0);
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (free_visited(visited, game->map_height),
			printf("Error\nMap must contain exactly one player\n"), 0);
	free_visited(visited, game->map_height);
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
