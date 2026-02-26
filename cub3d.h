/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:03:12 by albelaiz          #+#    #+#             */
/*   Updated: 2026/02/22 03:09:44 by yaamaich         ###   ########.fr       */
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
	double  player_dir;     /* radians */

	/* mlx */
	mlx_t       *mlx_ptr;
	mlx_image_t *img_ptr;

	/* ===== Raycasting state (like your t_data) ===== */
	int     x;
	int     y;

	/* angles */
	double  angle_deg;      /* player angle in degrees (0..360) */
	double  fov_deg;        /* ex: 60 */
	double  start_angle;
	double  angle_step;
	double  ray_angle;
	double  ray_rad;

	/* ray direction */
	double  ray_dir_x;
	double  ray_dir_y;

	/* dda */
	int     map_x;
	int     map_y;
	int     step_x;
	int     step_y;
	double  side_dist_x;
	double  side_dist_y;
	double  delta_dist_x;
	double  delta_dist_y;
	int     side;           /* 0 x-side, 1 y-side */
	int     hit;

	/* distance + projection */
	double  perp_wall_dist;
	double  wall_distance;
	int     wall_height;
	int     draw_start;
	int     draw_end;

	/* texture helpers (even if you don’t draw textures yet) */
	int     texnum;
	int     texx;

}   t_game;

void init_config(t_game *game);
int check_extension(char *file);
void parse_line(t_game *game , char *line);
void pars_texture(t_game *gmae, char *line , char type);
void parse_color(t_game *game, char *line, char type);
void pars_map_line(t_game *game, char *line);
int validate_all(t_game *game);
int normalize_map(t_game *g);
void draw_map(t_game *g);
void init_player(t_game *g);
void draw_player(t_game *g);
void handle_player_input(t_game *game);

/* raycasting api */
double  deg_to_rad(double deg);
double  rad_to_deg(double rad);
double  norm_deg(double a);

void    set_delta(t_game *g);
void    set_side_dist(t_game *g);
void    finding_hit(t_game *g);
void    set_texx(t_game *g, int tex_w);
void    set_texture(t_game *g, int tex_w);

double  cast_single_ray(t_game *g, double ray_angle_deg);
void    raycast(t_game *g, int x);
void    render_3d(t_game *g);

#endif