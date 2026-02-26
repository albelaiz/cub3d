/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:19:21 by albelaiz          #+#    #+#             */
/*   Updated: 2026/02/21 03:55:29 by yaamaich         ###   ########.fr       */
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
        pars_texture(game,trimmed,'N');
    else if (ft_strncmp(trimmed, "SO ",3) == 0)
        pars_texture(game,trimmed,'S');
    else if (ft_strncmp(trimmed, "WE ",3) == 0)
        pars_texture(game,trimmed,'W');
    else if (ft_strncmp(trimmed, "EA ",3) == 0)
        pars_texture(game,trimmed,'E');
    else if (ft_strncmp(trimmed, "F ",2) == 0)
        parse_color(game,trimmed,'F');
    else if (ft_strncmp(trimmed, "C ",2) == 0)
        parse_color(game,trimmed,'C');
    else
        pars_map_line(game,trimmed);
    free(trimmed);
}

void pars_texture(t_game *gmae, char *line , char type)
{
    char *path;
    path = ft_strtrim(line + 3, " \t");

    if (type == 'N')
    {
        if (gmae->path_no)
            printf("Error\nDuplicate NO texture\n");
        gmae->path_no = ft_strdup(path);
    }
    else if (type == 'S')
    {
        if (gmae->path_so)
            printf("Error\nDuplicate SO texture\n");
        gmae->path_so = ft_strdup(path);
    }
    else if (type == 'W')
    {
        if (gmae->path_we)
            printf("Error\nDuplicate WE texture\n");
        gmae->path_we = ft_strdup(path);
    }
    else if (type == 'E')
    {
        if (gmae->path_ea)
            printf("Error\nDuplicate EA texture\n");
        gmae->path_ea = ft_strdup(path);
    }
    free(path); 
}

void parse_color(t_game *game, char *line, char type)
{
    char **rgb;
    int r,g,b;
    rgb = ft_split(line +2,',');

    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        printf("Error\nInvalid RGB color values (must be 0-255)\n");
        free(rgb[0]);
        free(rgb[1]);
        free(rgb[2]);
        free(rgb);
        return;
    }

    if (type == 'F')
    {
        if (game->color_floor != -1)
            printf("Error\nDuplicate floor color (F)\n");
        game->color_floor = (r << 16) | (g << 8) | b;
    }
    else
    {
        if (game->color_ceiling != -1)
            printf("Error\nDuplicate ceiling color (C)\n");
        game->color_ceiling = (r << 16) | (g << 8) | b;
    }
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
            game->player_start_y = game->map_height;
            game->player_start_dir = line[x];
        }
        x++;
    }
    game->map_height++;
}
