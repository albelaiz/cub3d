/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:03:12 by albelaiz          #+#    #+#             */
/*   Updated: 2026/02/18 15:19:10 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/src/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "./minilibx/mlx.h"

typedef struct s_game
{
    //Parsed 
    
    // Resolution (R)
    int     win_width;
    int     win_height;

    // Texture Paths (NO, SO, WE, EA, S)
    char    *path_no;
    char    *path_so;
    char    *path_we;
    char    *path_ea;
    char    *path_sprite;

    // Colors (F, C)
    int     color_floor;
    int     color_ceiling;

    // Map Grid
    char    **map;
    int     map_width;
    int     map_height;

    // Player Start Info
    double  player_start_x;
    double  player_start_y;
    char    player_start_dir; // 'N', 'S', 'E', or 'W'

    /* --- MiniLibX / Game State (for later) --- */
    
    void    *mlx_ptr;
    void    *win_ptr;
    // ...texture image pointers...

}   t_game;

void init_config(t_game *game);
int check_extension(char *file);
void parse_line(t_game *game , char *line);
void pars_texture(t_game *gmae, char *line , char type);
void parse_color(t_game *game, char *line, char type);
void pars_map_line(t_game *game, char *line);
int validate_all(t_game *game);
#endif