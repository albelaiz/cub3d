/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:56:50 by albelaiz          #+#    #+#             */
/*   Updated: 2026/03/10 12:40:29 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define TILE 10

static void draw_square(t_game *g, int start_x, int start_y, int size, uint32_t color)
{
	int x;
	int y;
	int end_x;
	int end_y;

	if (start_x < 0)
		start_x = 0;
	if (start_y < 0)
		start_y = 0;

	end_x = start_x + size;
	end_y = start_y + size;

	if (end_x > (int)g->img_ptr->width)
		end_x = (int)g->img_ptr->width;
	if (end_y > (int)g->img_ptr->height)
		end_y = (int)g->img_ptr->height;

	y = start_y;
	while (y < end_y)
	{
		x = start_x;
		while (x < end_x)
		{
			mlx_put_pixel(g->img_ptr, x, y, color);
			x++;
		}
		y++;
	}
}

void draw_map(t_game *g)
{
    for (int y = 0; y < g->map_height; y++)
    {
        for (int x = 0; x < g->map_width; x++)
        {
            char tile = g->map[y][x];

            if (tile == '1')
                draw_square(g, x * TILE, y * TILE, TILE, 0xFF888888);
            else if (tile == '0')
                draw_square(g, x * TILE, y * TILE, TILE, 0xFF000000);
            else
                draw_square(g, x * TILE, y * TILE, TILE, 0xFF202020); // void/space
        }
    }
}

void draw_player(t_game *g)
{
    int px = (int)(g->player_x * TILE);
    int py = (int)(g->player_y * TILE);

    // small square marker
    draw_square(g, px - 3, py - 3, 6, 0xFF0000FF);
}
static void clear_image(mlx_image_t *img, uint32_t color)
{
	for (uint32_t y = 0; y < img->height; y++)
		for (uint32_t x = 0; x < img->width; x++)
			mlx_put_pixel(img, x, y, color);
}

static void update(void *param)
{
	t_game *g = (t_game *)param;

	handle_player_input(g);

	clear_image(g->img_ptr, 0xFF000000);
	render_3d(g);
	draw_map(g);
	draw_player(g);
}

void ff()
{
	system("leaks -q cub3D");
}

int main(int ac , char **av)
{
	t_game game;
	int fd;
	char  *line;


	atexit(ff);
	if (ac != 2)
	{
		printf("Error\nUsage: ./cub3d <map.cub>\n");
		exit(1);
	}
	if (!check_extension(av[1]))
	{
		printf("Error\nMap file must have .cub extension\n");
		exit(1);
	}
	fd = open(av[1],O_RDONLY);
	if (fd < 0)
		return (printf("Error\nCannot open file\n"), 1);
	init_config(&game);
	line = get_next_line(fd);
	while(line != NULL)
	{
		parse_line(&game, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	
	// Validate parsed data
	if (!validate_all(&game))
		return (1);
	init_player(&game);
	load_textures(&game);
	game.mlx_ptr = mlx_init(800, 600, "Square", true);
	game.img_ptr = mlx_new_image(game.mlx_ptr, 800, 600);
	if (!game.img_ptr)
		return (EXIT_FAILURE);
	mlx_image_to_window(game.mlx_ptr, game.img_ptr, 0, 0);
	mlx_loop_hook(game.mlx_ptr, update, &game);
	mlx_loop(game.mlx_ptr);
	mlx_terminate(game.mlx_ptr);

	return(0);
}