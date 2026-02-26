/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 14:20:00 by albelaiz          #+#    #+#             */
/*   Updated: 2026/02/22 01:37:40 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_missing_elements(t_game *game)
{
	if (!game->path_no)
		return (printf("Error\nMissing NO texture\n"), 0);
	if (!game->path_so)
		return (printf("Error\nMissing SO texture\n"), 0);
	if (!game->path_we)
		return (printf("Error\nMissing WE texture\n"), 0);
	if (!game->path_ea)
		return (printf("Error\nMissing EA texture\n"), 0);
	if (game->color_floor == -1)
		return (printf("Error\nMissing floor color (F)\n"), 0);
	if (game->color_ceiling == -1)
		return (printf("Error\nMissing ceiling color (C)\n"), 0);
	return (1);
}

int	count_players(t_game *game)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
				game->map[i][j] == 'E' || game->map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	validate_player(t_game *game)
{
	int	player_count;

	player_count = count_players(game);
	if (player_count == 0)
		return (printf("Error\nNo player position in map\n"), 0);
	if (player_count > 1)
		return (printf("Error\nMultiple players in map\n"), 0);
	return (1);
}

int	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	validate_map_characters(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!is_valid_map_char(game->map[i][j]))
			{
				printf("Error\nInvalid character '%c' in map at line %d\n",
					game->map[i][j], i + 1);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

// int	check_position(t_game *game, int y, int x)
// {
// 	if (y < 0 || y >= game->map_height)
// 		return (0);
// 	if (x < 0 || x >= (int)ft_strlen(game->map[y]))
// 		return (0);
// 	if (game->map[y][x] == ' ')
// 		return (0);
// 	return (1);
// }

int	check_position(t_game *game, int y, int x)
{
	if (y < 0 || y >= game->map_height)
		return (0);
	if (x < 0 || x >= game->map_width)
		return (0);
	if (game->map[y][x] == ' ')
		return (0);
	return (1);
}

int	validate_map_closed(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '0' || game->map[i][j] == 'N' ||
				game->map[i][j] == 'S' || game->map[i][j] == 'E' ||
				game->map[i][j] == 'W')
			{
				if (!check_position(game, i - 1, j) ||
					!check_position(game, i + 1, j) ||
					!check_position(game, i, j - 1) ||
					!check_position(game, i, j + 1))
				{
					printf("Error\nMap not closed at position (%d, %d)\n", i, j);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

// int	validate_all(t_game *game)
// {
// 	if (!validate_missing_elements(game))
// 		return (0);
// 	if (!validate_player(game))
// 		return (0);
// 	if (!validate_map_characters(game))
// 		return (0);
// 	if (!validate_map_closed(game))
// 		return (0);
// 	return (1);
// }
int	validate_all(t_game *game)
{
	if (!validate_missing_elements(game))
		return (0);

	if (!normalize_map(game))
		return (0);

	if (!validate_player(game))
		return (0);
	if (!validate_map_characters(game))
		return (0);
	if (!validate_map_closed(game))
		return (0);
	return (1);
}