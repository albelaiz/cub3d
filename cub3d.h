/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:03:12 by albelaiz          #+#    #+#             */
/*   Updated: 2026/02/26 12:01:32 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H

# include "./libft/src/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "./MLX42-master/include/MLX42/MLX42.h"

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	cam_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	double	side_x;
	double	side_y;
	int		side;
	double	wall_x;
}	t_ray;

typedef struct s_game
{
	int     win_width;
	int     win_height;

	char    *path_no;
	char    *path_so;
	char    *path_we;
	char    *path_ea;
	char    *path_sprite;

	int     color_floor;
	int     color_ceiling;

	char    **map;
	int     map_width;
	int     map_height;

	double  player_start_x;
	double  player_start_y;
	char    player_start_dir;

	double  player_x;
	double  player_y;
	double  player_dir;

	mlx_t       *mlx_ptr;
	mlx_image_t *img_ptr;
	mlx_texture_t   *tex_no;
	mlx_texture_t   *tex_so;
	mlx_texture_t   *tex_we;
	mlx_texture_t   *tex_ea;

}   t_game;

/* utils.c */
int     check_extension(char *file);
void    init_config(t_game *game);
void    cleanup_game(t_game *game);

/* parse.c */
void    parse_line(t_game *game, char *line);
void    pars_texture(t_game *game, char *line, char type);
void    parse_color(t_game *game, char *line, char type);
void    pars_map_line(t_game *game, char *line);

/* validation.c */
int     validate_all(t_game *game);

/* map_normalize.c */
int     normalize_map(t_game *g);

/* player_init.c */
void    init_player(t_game *g);
double  deg_to_rad(double deg);
double  rad_to_deg(double rad);
double  norm_deg(double a);

/* main.c */
void    draw_map(t_game *g);
void    draw_player(t_game *g);

/* move_player.c */
void    handle_player_input(t_game *game);

/* recasting.c */
void    render_3d(t_game *g);

/* recasting_utils.c */
void    draw_background(t_game *g);
void    draw_vline(t_game *g, int x, int y0, int y1, uint32_t color);

/* recasting_ray.c */
void    init_ray(t_game *g, int x, t_ray *r);
void    setup_steps(t_game *g, t_ray *r);
int     dda_loop(t_game *g, t_ray *r);
void    cast_and_draw(t_game *g, int x);

/* recasting_tex.c */
int             load_textures(t_game *g);
uint32_t        get_tex_pixel(mlx_texture_t *tex, int tx, int ty);
mlx_texture_t   *get_wall_texture(t_game *g, t_ray *r);
void            draw_textured_vline(t_game *g, int x, t_ray *r, double perp);

#endif