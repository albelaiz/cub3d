/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelaiz <albelaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:19:21 by albelaiz          #+#    #+#             */
/*   Updated: 2025/11/17 16:16:03 by albelaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void parse_line(t_game *game , char *line)
{
    char *trimmed = ft_strtrim(line, " \t\n");
    if (!trimmed || trimmed[0] == '\0')
    {
        free(trimmed);
        return;
    }
    if (ft_strncmp(trimmed, "NO ",3) == 0)
        parse_texture(game,trimmed,'N');
    else if (ft_strncmp(trimmed, "SO ",3) == 0)
        parse_texture(game,trimmed,'S');
    else if (ft_strncmp(trimmed, "WE ",3) == 0)
        parse_texture(game,trimmed,'W');
    else if (ft_strncmp(trimmed, "EA ",3) == 0)
        parse_texture(game,trimmed,'E');
    else if (ft_strncmp(trimmed, "F ",2) == 0)
        parse_texture(game,trimmed,'F');
    else if (ft_strncmp(trimmed, "C ",2) == 0)
        parse_texture(game,trimmed,'C');
    else
        pars_map_line(game,trimmed);
    free(trimmed);
}
void pars_texture(t_game *gmae, char *line , char type)
{
    char *path;
    path = ft_strtrim(line + 3, " \t");

    if (type == 'N')
        gmae->path_no = ft_strdup(path);
    else if (type == 'S')
        gmae->path_so = ft_strdup(path);
    else if (type == 'W')
        gmae->path_we = ft_strdup(path);
    else if (type == 'E')
        gmae->path_ea = ft_strdup(path);
    free(path); 
}