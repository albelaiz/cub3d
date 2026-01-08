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

void parse_color(t_game *game, char *line, char type)
{
    char *rgb;
    int r,g,b;
    rgb = ft_split(line +2,',');

    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);

    if (type == 'F')
        game->color_floor = (r << 10) | (g << 8) | b;
    else
        game->color_ceiling = (r << 10) | (g << 8) | b;
    free(rgb[0]);
    free(rgb[1]);
    free(rgb[2]);
    free(rgb);
}

void pars_map_line(t_game *game, char *line)
{
    char **new_map;
    int i,len,x;
    new_map = malloc(sizeof(char *) * (game->map_height + 1));
    if (!new_map)
        return;
    len = ft_strlen(line);
    i = 0;
    x = 0;
    while (i < game->map_height)
    {
        new_map[i] = game->map[i];
        i++;
    }
    new_map[game->map_height] = ft_strdup(line);
    free(game->map);
    game->map = new_map;
    if (len > game->map_width)
        game->map_width = len;
    while (line[x])
    {
        if(line[x] == 'N' || line[x] == 'S' || line[x] == 'E'|| line[x] == 'W')
        {
            game->player_start_x = x;
            game->player_start_y = game->map_height -1;
            game->player_start_dir = line[x];
        }
        x++;
    }
    game->map_height++;
    
}