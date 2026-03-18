/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:56:50 by albelaiz          #+#    #+#             */
/*   Updated: 2026/03/18 10:25:09 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	close_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	exit(exit_game(game, EXIT_SUCCESS));
}

static void	update(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	handle_player_input(g);
	clear_image(g->img_ptr, 0xFF000000);
	render_3d(g);
	draw_map(g);
	draw_player(g);
}

void	ff(void)
{
	system("leaks -q cub3D");
}

int	main(int ac, char **av)
{
	t_game	game;
	int		fd;

	atexit(ff);
	if (!handle_args(ac, av))
		exit(1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (printf("Error\nCannot open file\n"), 1);
	init_config(&game);
	if (!read_map_file(&game, fd))
		return (exit_game(&game, 1));
	if (!validate_all(&game))
		return (exit_game(&game, 1));
	init_player(&game);
	if (!load_textures(&game))
		return (exit_game(&game, 1));
	if (!init_game_window(&game))
		return (exit_game(&game, EXIT_FAILURE));
	mlx_close_hook(game.mlx_ptr, close_game, &game);
	mlx_loop_hook(game.mlx_ptr, update, &game);
	mlx_loop(game.mlx_ptr);
	return (exit_game(&game, 0));
}
