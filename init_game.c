/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 04:08:44 by yaamaich          #+#    #+#             */
/*   Updated: 2026/03/18 10:02:21 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_game(t_game *game, int status)
{
	cleanup_game(game);
	return (status);
}

int	handle_args(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error\nUsage: ./cub3d <map.cub>\n");
		return (0);
	}
	if (!check_extension(av[1]))
	{
		printf("Error\nMap file must have .cub extension\n");
		return (0);
	}
	return (1);
}

int	read_map_file(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		parse_line(game, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	init_game_window(t_game *game)
{
	game->mlx_ptr = mlx_init(800, 600, "cub3D", true);
	if (!game->mlx_ptr)
		return (0);
	game->img_ptr = mlx_new_image(game->mlx_ptr, 800, 600);
	if (!game->img_ptr)
		return (0);
	if (mlx_image_to_window(game->mlx_ptr, game->img_ptr, 0, 0) < 0)
		return (0);
	return (1);
}
