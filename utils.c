/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelaiz <albelaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:16:38 by albelaiz          #+#    #+#             */
/*   Updated: 2025/11/17 16:16:49 by albelaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_extension(char *file)
{
    int len;
    len = ft_strlen(file);

    if (len < 4)
        return(0);
    if (ft_strncmp(file + len - 4,".cub",4))
        return(0);
    return(1);
}

void init_config(t_game *game)
{
    game->path_no = NULL;
    game->path_so = NULL;
    game->path_ea = NULL;
    game->path_we = NULL;
    game->path_sprite = NULL;
    game->map= NULL;
    
    game->win_width = 0;
    game->win_height = 0;
    game->color_floor = -1;
    game->color_ceiling = -1;
    game->map_width = 0;
    game->map_height = 0;
    game->player_start_x = 0;
    game->player_start_y = 0;
    game->player_start_dir = 0;
}