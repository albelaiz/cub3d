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
    fd = open(fd,"map1.cub",O_RDWR);
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
    return(0);
}