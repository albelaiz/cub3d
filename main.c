/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelaiz <albelaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:56:50 by albelaiz          #+#    #+#             */
/*   Updated: 2025/11/17 16:11:45 by albelaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac , char **av)
{
    t_game game;
    int fd;
    char  *line;

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
    
    // Debug output - print what we parsed
    printf("\n=== Parsing Results ===\n");
    printf("North texture: %s\n", game.path_no);
    printf("South texture: %s\n", game.path_so);
    printf("West texture: %s\n", game.path_we);
    printf("East texture: %s\n", game.path_ea);
    printf("Floor color: %d (0x%X)\n", game.color_floor, game.color_floor);
    printf("Ceiling color: %d (0x%X)\n", game.color_ceiling, game.color_ceiling);
    printf("Map width: %d\n", game.map_width);
    printf("Map height: %d\n", game.map_height);
    printf("Player start: (%.0f, %.0f) facing '%c'\n", 
           game.player_start_x, game.player_start_y, game.player_start_dir);
    printf("\nMap:\n");
    for (int i = 0; i < game.map_height; i++)
        printf("%s\n", game.map[i]);
    
    return(0);
}