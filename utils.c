/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelaiz <albelaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:16:38 by albelaiz          #+#    #+#             */
/*   Updated: 2026/03/14 12:31:29 by albelaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void free_map(char **map, int map_height)
{
    int i;

    if (!map)
        return;
    i = 0;
    while (i < map_height)
    {
        free(map[i]);
        i++;
    }
    free(map);
}

int check_extension(char *file)
{
    int len;
    len = ft_strlen(file);

    if (len < 4)
        return (0);
    if (ft_strncmp(file + len - 4, ".cub", 4) != 0)
        return (0);
    return (1);
}

void    init_config(t_game *game)
{
    game->path_no = NULL;
    game->path_so = NULL;
    game->path_ea = NULL;
    game->path_we = NULL;
    game->path_sprite = NULL;
    game->map = NULL;

    game->win_width = 0;
    game->win_height = 0;
    game->color_floor = -1;
    game->color_ceiling = -1;
    game->map_width = 0;
    game->map_height = 0;
    game->player_start_x = 0;
    game->player_start_y = 0;
    game->player_start_dir = 0;
    game->mlx_ptr = NULL;
    game->img_ptr = NULL;
    game->tex_no = NULL;
    game->tex_so = NULL;
    game->tex_we = NULL;
    game->tex_ea = NULL;
}

void    cleanup_game(t_game *game)
{
    if (!game)
        return;
    if (game->img_ptr && game->mlx_ptr)
        mlx_delete_image(game->mlx_ptr, game->img_ptr);
    if (game->tex_no)
        mlx_delete_texture(game->tex_no);
    if (game->tex_so)
        mlx_delete_texture(game->tex_so);
    if (game->tex_we)
        mlx_delete_texture(game->tex_we);
    if (game->tex_ea)
        mlx_delete_texture(game->tex_ea);
    if (game->mlx_ptr)
        mlx_terminate(game->mlx_ptr);
    free_map(game->map, game->map_height);
    free(game->path_no);
    free(game->path_so);
    free(game->path_we);
    free(game->path_ea);
    free(game->path_sprite);
    game->img_ptr = NULL;
    game->tex_no = NULL;
    game->tex_so = NULL;
    game->tex_we = NULL;
    game->tex_ea = NULL;
    game->mlx_ptr = NULL;
    game->map = NULL;
    game->path_no = NULL;
    game->path_so = NULL;
    game->path_we = NULL;
    game->path_ea = NULL;
    game->path_sprite = NULL;
}
