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
